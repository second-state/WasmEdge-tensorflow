// SPDX-License-Identifier: Apache-2.0
#include <fstream>
#include <string>
#include <vector>

#include <boost/gil.hpp>
#include <boost/gil/extension/io/jpeg.hpp>
#include <boost/gil/extension/numeric/resample.hpp>
#include <boost/gil/extension/numeric/sampler.hpp>
#include <boost/gil/io/read_image.hpp>
#include <tensorflow/c/c_api.h>

#include "common/log.h"
#include "tensorflow_func.h"

namespace SSVM {
namespace Host {

Expect<uint32_t> SSVMTensorflowMobilenetv2::body(
    Runtime::Instance::MemoryInstance *MemInst, uint32_t ModNamePtr,
    uint32_t ModNameLen, uint32_t InputPtr, uint32_t InputLen,
    uint32_t OutputPtr, uint32_t OutputLen, uint32_t ImgNamePtr,
    uint32_t ImgNameLen, uint32_t TargetImgW, uint32_t TargetImgH) {

  std::string ModName(MemInst->getPointer<char *>(ModNamePtr), ModNameLen);
  std::string ModInput(MemInst->getPointer<char *>(InputPtr), InputLen);
  std::string ModOutput(MemInst->getPointer<char *>(OutputPtr), OutputLen);
  std::string ImgName(MemInst->getPointer<char *>(ImgNamePtr), ImgNameLen);

  /// Read model to buffer.
  std::ifstream ModFS(ModName, std::ios::binary | std::ios::ate);
  if (ModFS.fail()) {
    LOG(ERROR) << "ssvm_tensorflow_Mobilenetv2: Cannot open model file "
               << ModName;
    return 1;
  }
  std::vector<uint8_t> Mod(ModFS.tellg());
  ModFS.seekg(0, std::ios::beg);
  ModFS.read(reinterpret_cast<char *>(Mod.data()), Mod.size());

  /// Read image and resize to buffer.
  boost::gil::rgb8_image_t Img;
  try {
    boost::gil::read_image(ImgName, Img, boost::gil::jpeg_tag());
  } catch (const std::ios_base::failure &e) {
    LOG(ERROR) << "ssvm_tensorflow_Mobilenetv2: Cannot open image file "
               << ImgName;
    return 1;
  }
  std::vector<uint8_t> ImgData(3 * TargetImgW * TargetImgH);
  boost::gil::rgb8_view_t ImgView = boost::gil::interleaved_view(
      TargetImgW, TargetImgH, (boost::gil::rgb8_pixel_t *)(&ImgData[0]),
      TargetImgW * 3 * sizeof(uint8_t));
  boost::gil::resize_view(boost::gil::const_view(Img), ImgView,
                          boost::gil::bilinear_sampler());
  std::vector<float> Flat(3 * TargetImgW * TargetImgH);
  std::transform(ImgData.begin(), ImgData.end(), Flat.begin(),
                 [](uint8_t P) -> float { return P / 255.0; });

  /// Status
  TF_Status *Stat = TF_NewStatus();

  /// Graph
  TF_Graph *Graph = TF_NewGraph();
  TF_Buffer *ModBuf = TF_NewBufferFromString(&Mod[0], Mod.size());
  TF_ImportGraphDefOptions *GraphOpts = TF_NewImportGraphDefOptions();
  TF_GraphImportGraphDef(Graph, ModBuf, GraphOpts, Stat);
  if (TF_GetCode(Stat) != TF_OK) {
    LOG(ERROR) << "ssvm_tensorflow_Mobilenetv2: Cannot import graph: "
               << TF_Message(Stat);
    return 1;
  }

  /// Input tensor and data copying
  int64_t Dims[4] = {1, static_cast<int64_t>(TargetImgW),
                     static_cast<int64_t>(TargetImgH), 3};
  TF_Tensor *InTensor =
      TF_AllocateTensor(TF_FLOAT, Dims, 4, Flat.size() * sizeof(float));
  if (InTensor == nullptr) {
    LOG(ERROR)
        << "ssvm_tensorflow_Mobilenetv2: Unable to allocate input tensor";
    return 1;
  }
  float *InTensorData = static_cast<float *>(TF_TensorData(InTensor));
  std::copy_n(Flat.begin(), Flat.size(), InTensorData);
  TF_Output Inputs = {TF_GraphOperationByName(Graph, ModInput.c_str()), 0};

  /// Output tensor
  TF_Tensor *OutTensor = nullptr;
  TF_Output Outputs = {TF_GraphOperationByName(Graph, ModOutput.c_str()), 0};

  /// Session
  TF_SessionOptions *SessionOpts = TF_NewSessionOptions();
  TF_Session *Session = TF_NewSession(Graph, SessionOpts, Stat);
  if (TF_GetCode(Stat) != TF_OK) {
    LOG(ERROR) << "ssvm_tensorflow_Mobilenetv2: Unable to create session: "
               << TF_Message(Stat);
    return 1;
  }

  /// Run session
  TF_SessionRun(Session,
                // RunOptions
                nullptr,
                // Input tensors
                &Inputs, &InTensor, 1,
                // Output tensors
                &Outputs, &OutTensor, 1,
                // Target operations
                nullptr, 0,
                // RunMetadata
                nullptr,
                // Output status
                Stat);
  if (TF_GetCode(Stat) != TF_OK) {
    LOG(ERROR) << "ssvm_tensorflow_Mobilenetv2: Unable to run session: "
               << TF_Message(Stat);
    return 1;
  }

  /// Print results
  float *OutTensorData = static_cast<float *>(TF_TensorData(OutTensor));
  uint32_t NOut = TF_TensorByteSize(OutTensor) / sizeof(float);
  Env.Res.clear();
  Env.Res.str("");
  Env.Res << "[";
  for (uint32_t I = 0; I < NOut - 1; I++) {
    Env.Res << std::fixed << std::setprecision(20) << OutTensorData[I] << ",";
  }
  Env.Res << std::fixed << std::setprecision(20) << OutTensorData[NOut - 1]
          << "]";

  /// Free resources
  TF_CloseSession(Session, Stat);
  TF_DeleteSession(Session, Stat);
  TF_DeleteSessionOptions(SessionOpts);
  TF_DeleteGraph(Graph);
  TF_DeleteImportGraphDefOptions(GraphOpts);
  TF_DeleteTensor(InTensor);
  TF_DeleteTensor(OutTensor);
  TF_DeleteStatus(Stat);

  return 0;
}

Expect<uint32_t>
SSVMTensorflowGetResultLen::body(Runtime::Instance::MemoryInstance *MemInst) {
  return Env.Res.str().size();
}

Expect<void>
SSVMTensorflowGetResult::body(Runtime::Instance::MemoryInstance *MemInst,
                              uint32_t BufPtr) {
  /// Check memory instance from module.
  if (MemInst == nullptr) {
    return Unexpect(ErrCode::ExecutionFailed);
  }

  char *Buf = MemInst->getPointer<char *>(BufPtr);
  std::copy_n(Env.Res.str().begin(), Env.Res.str().size(), Buf);
  return {};
}

} // namespace Host
} // namespace SSVM
