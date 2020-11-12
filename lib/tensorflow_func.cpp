// SPDX-License-Identifier: Apache-2.0
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include <boost/gil.hpp>
#include <boost/gil/extension/io/jpeg.hpp>
#include <boost/gil/extension/io/png.hpp>
#include <boost/gil/extension/numeric/resample.hpp>
#include <boost/gil/extension/numeric/sampler.hpp>
#include <boost/gil/io/read_image.hpp>
#include <tensorflow/c/c_api.h>

#include "common/log.h"
#include "common/span.h"
#include "tensorflow_func.h"

namespace SSVM {
namespace Host {

namespace {
/// Helper function to read jpeg buffer to gil::image
template <typename Image, typename FormatTag>
bool readBufToImg(const char *Buf, uint32_t Len, Image &Img,
                  FormatTag const &FTag) {
  std::stringstream ImgStream;
  ImgStream.write(Buf, Len);
  try {
    boost::gil::read_image(ImgStream, Img, FTag);
  } catch (std::exception const &e) {
    LOG(ERROR) << e.what() << std::endl;
    return false;
  }
  return true;
}

/// Helper function to resize image. 8-bit depth only.
template <typename Image>
std::vector<uint8_t> resizeImg(const Image &Img, uint32_t W, uint32_t H) {
  uint32_t C = boost::gil::num_channels<typename Image::view_t>::value;
  std::vector<uint8_t> ImgData(C * W * H);
  typename Image::view_t ImgView = boost::gil::interleaved_view(
      W, H, (typename Image::value_type *)(&ImgData[0]),
      W * C * sizeof(uint8_t));
  boost::gil::resize_view(boost::gil::const_view(Img), ImgView,
                          boost::gil::bilinear_sampler());
  return ImgData;
}

/// Helper function to normalize and resize image
std::vector<float> normalizeImg(Span<const uint8_t> V) {
  std::vector<float> Flat(V.size());
  std::transform(V.begin(), V.end(), Flat.begin(),
                 [](uint8_t P) -> float { return P / 255.0; });
  return Flat;
}

/// Helper function to run tensorflow session
bool runTFSession(const char *ModelBuf, uint32_t ModelLen,
                  std::vector<std::string> &InputNames,
                  std::vector<TF_Tensor *> &InTensor,
                  std::vector<std::string> &OutputNames,
                  std::vector<TF_Tensor *> &OutTensor) {
  /// Tensorflow Status
  TF_Status *Stat = TF_NewStatus();

  /// Tensorflow Graph
  TF_Graph *Graph = TF_NewGraph();
  TF_Buffer *ModBuf = TF_NewBufferFromString(ModelBuf, ModelLen);
  TF_ImportGraphDefOptions *GraphOpts = TF_NewImportGraphDefOptions();
  TF_GraphImportGraphDef(Graph, ModBuf, GraphOpts, Stat);
  if (TF_GetCode(Stat) != TF_OK) {
    LOG(ERROR) << "Cannot import graph: " << TF_Message(Stat);
    TF_DeleteImportGraphDefOptions(GraphOpts);
    TF_DeleteGraph(Graph);
    TF_DeleteBuffer(ModBuf);
    TF_DeleteStatus(Stat);
    return false;
  }

  /// Input and output tensor
  std::vector<TF_Output> Inputs;
  for (auto &S : InputNames) {
    Inputs.emplace_back(
        TF_Output{TF_GraphOperationByName(Graph, S.c_str()), 0});
  }
  std::vector<TF_Output> Outputs;
  for (auto &S : OutputNames) {
    Outputs.emplace_back(
        TF_Output{TF_GraphOperationByName(Graph, S.c_str()), 0});
  }

  /// Tensorflow Session
  TF_SessionOptions *SessionOpts = TF_NewSessionOptions();
  TF_Session *Session = TF_NewSession(Graph, SessionOpts, Stat);
  if (TF_GetCode(Stat) != TF_OK) {
    LOG(ERROR) << "Unable to create session: " << TF_Message(Stat);
    TF_DeleteImportGraphDefOptions(GraphOpts);
    TF_DeleteGraph(Graph);
    TF_DeleteBuffer(ModBuf);
    TF_DeleteSessionOptions(SessionOpts);
    TF_DeleteStatus(Stat);
    return false;
  }

  /// Run session
  TF_SessionRun(Session,
                // RunOptions
                nullptr,
                // Input tensors
                &Inputs[0], &InTensor[0], Inputs.size(),
                // Output tensors
                &Outputs[0], &OutTensor[0], Outputs.size(),
                // Target operations
                nullptr, 0,
                // RunMetadata
                nullptr,
                // Output status
                Stat);

  /// Free resources
  TF_CloseSession(Session, Stat);
  TF_DeleteSession(Session, Stat);
  TF_DeleteSessionOptions(SessionOpts);
  TF_DeleteGraph(Graph);
  TF_DeleteImportGraphDefOptions(GraphOpts);

  if (TF_GetCode(Stat) != TF_OK) {
    LOG(ERROR) << "Unable to run session: " << TF_Message(Stat);
    TF_DeleteStatus(Stat);
    return false;
  }
  TF_DeleteStatus(Stat);
  return true;
}

} // namespace

Expect<uint32_t>
SSVMTensorflowLoadJPGToRGB8::body(Runtime::Instance::MemoryInstance *MemInst,
                                  uint32_t ImgBufPtr, uint32_t ImgBufLen,
                                  uint32_t TargetImgW, uint32_t TargetImgH) {
  /// Check memory instance from module.
  if (MemInst == nullptr) {
    return Unexpect(ErrCode::ExecutionFailed);
  }

  boost::gil::rgb8_image_t Img;
  if (!readBufToImg(MemInst->getPointer<char *>(ImgBufPtr), ImgBufLen, Img,
                    boost::gil::jpeg_tag())) {
    return 1;
  }
  auto Resized = resizeImg(Img, TargetImgW, TargetImgH);
  Env.Res.clear();
  Env.Res.str("");
  Env.Res.write(reinterpret_cast<const char *>(&Resized[0]),
                sizeof(uint8_t) * Resized.size());
  return 0;
}

Expect<uint32_t>
SSVMTensorflowLoadJPGToBGR8::body(Runtime::Instance::MemoryInstance *MemInst,
                                  uint32_t ImgBufPtr, uint32_t ImgBufLen,
                                  uint32_t TargetImgW, uint32_t TargetImgH) {
  /// Check memory instance from module.
  if (MemInst == nullptr) {
    return Unexpect(ErrCode::ExecutionFailed);
  }

  boost::gil::bgr8_image_t Img;
  if (!readBufToImg(MemInst->getPointer<char *>(ImgBufPtr), ImgBufLen, Img,
                    boost::gil::jpeg_tag())) {
    return 1;
  }
  auto Resized = resizeImg(Img, TargetImgW, TargetImgH);
  Env.Res.clear();
  Env.Res.str("");
  Env.Res.write(reinterpret_cast<const char *>(&Resized[0]),
                sizeof(uint8_t) * Resized.size());
  return 0;
}

Expect<uint32_t>
SSVMTensorflowLoadJPGToRGB32F::body(Runtime::Instance::MemoryInstance *MemInst,
                                    uint32_t ImgBufPtr, uint32_t ImgBufLen,
                                    uint32_t TargetImgW, uint32_t TargetImgH) {
  /// Check memory instance from module.
  if (MemInst == nullptr) {
    return Unexpect(ErrCode::ExecutionFailed);
  }

  boost::gil::rgb8_image_t Img;
  if (!readBufToImg(MemInst->getPointer<char *>(ImgBufPtr), ImgBufLen, Img,
                    boost::gil::jpeg_tag())) {
    return 1;
  }
  auto Resized = resizeImg(Img, TargetImgW, TargetImgH);
  auto Flat = normalizeImg(Resized);
  Env.Res.clear();
  Env.Res.str("");
  Env.Res.write(reinterpret_cast<const char *>(&Flat[0]),
                sizeof(float) * Flat.size());
  return 0;
}

Expect<uint32_t>
SSVMTensorflowLoadJPGToBGR32F::body(Runtime::Instance::MemoryInstance *MemInst,
                                    uint32_t ImgBufPtr, uint32_t ImgBufLen,
                                    uint32_t TargetImgW, uint32_t TargetImgH) {
  /// Check memory instance from module.
  if (MemInst == nullptr) {
    return Unexpect(ErrCode::ExecutionFailed);
  }

  boost::gil::bgr8_image_t Img;
  if (!readBufToImg(MemInst->getPointer<char *>(ImgBufPtr), ImgBufLen, Img,
                    boost::gil::jpeg_tag())) {
    return 1;
  }
  auto Resized = resizeImg(Img, TargetImgW, TargetImgH);
  auto Flat = normalizeImg(Resized);
  Env.Res.clear();
  Env.Res.str("");
  Env.Res.write(reinterpret_cast<const char *>(&Flat[0]),
                sizeof(float) * Flat.size());
  return 0;
}

Expect<uint32_t>
SSVMTensorflowLoadPNGToRGB8::body(Runtime::Instance::MemoryInstance *MemInst,
                                  uint32_t ImgBufPtr, uint32_t ImgBufLen,
                                  uint32_t TargetImgW, uint32_t TargetImgH) {
  /// Check memory instance from module.
  if (MemInst == nullptr) {
    return Unexpect(ErrCode::ExecutionFailed);
  }

  boost::gil::rgb8_image_t Img;
  if (!readBufToImg(MemInst->getPointer<char *>(ImgBufPtr), ImgBufLen, Img,
                    boost::gil::png_tag())) {
    return 1;
  }
  auto Resized = resizeImg(Img, TargetImgW, TargetImgH);
  Env.Res.clear();
  Env.Res.str("");
  Env.Res.write(reinterpret_cast<const char *>(&Resized[0]),
                sizeof(uint8_t) * Resized.size());
  return 0;
}

Expect<uint32_t>
SSVMTensorflowLoadPNGToBGR8::body(Runtime::Instance::MemoryInstance *MemInst,
                                  uint32_t ImgBufPtr, uint32_t ImgBufLen,
                                  uint32_t TargetImgW, uint32_t TargetImgH) {
  /// Check memory instance from module.
  if (MemInst == nullptr) {
    return Unexpect(ErrCode::ExecutionFailed);
  }

  boost::gil::bgr8_image_t Img;
  if (!readBufToImg(MemInst->getPointer<char *>(ImgBufPtr), ImgBufLen, Img,
                    boost::gil::png_tag())) {
    return 1;
  }
  auto Resized = resizeImg(Img, TargetImgW, TargetImgH);
  Env.Res.clear();
  Env.Res.str("");
  Env.Res.write(reinterpret_cast<const char *>(&Resized[0]),
                sizeof(uint8_t) * Resized.size());
  return 0;
}

Expect<uint32_t>
SSVMTensorflowLoadPNGToRGB32F::body(Runtime::Instance::MemoryInstance *MemInst,
                                    uint32_t ImgBufPtr, uint32_t ImgBufLen,
                                    uint32_t TargetImgW, uint32_t TargetImgH) {
  /// Check memory instance from module.
  if (MemInst == nullptr) {
    return Unexpect(ErrCode::ExecutionFailed);
  }

  boost::gil::rgb8_image_t Img;
  if (!readBufToImg(MemInst->getPointer<char *>(ImgBufPtr), ImgBufLen, Img,
                    boost::gil::png_tag())) {
    return 1;
  }
  auto Resized = resizeImg(Img, TargetImgW, TargetImgH);
  auto Flat = normalizeImg(Resized);
  Env.Res.clear();
  Env.Res.str("");
  Env.Res.write(reinterpret_cast<const char *>(&Flat[0]),
                sizeof(float) * Flat.size());
  return 0;
}

Expect<uint32_t>
SSVMTensorflowLoadPNGToBGR32F::body(Runtime::Instance::MemoryInstance *MemInst,
                                    uint32_t ImgBufPtr, uint32_t ImgBufLen,
                                    uint32_t TargetImgW, uint32_t TargetImgH) {
  /// Check memory instance from module.
  if (MemInst == nullptr) {
    return Unexpect(ErrCode::ExecutionFailed);
  }

  boost::gil::bgr8_image_t Img;
  if (!readBufToImg(MemInst->getPointer<char *>(ImgBufPtr), ImgBufLen, Img,
                    boost::gil::png_tag())) {
    return 1;
  }
  auto Resized = resizeImg(Img, TargetImgW, TargetImgH);
  auto Flat = normalizeImg(Resized);
  Env.Res.clear();
  Env.Res.str("");
  Env.Res.write(reinterpret_cast<const char *>(&Flat[0]),
                sizeof(float) * Flat.size());
  return 0;
}

Expect<uint32_t>
SSVMTensorflowRunVision::body(Runtime::Instance::MemoryInstance *MemInst,
                              uint32_t ModBufPtr, uint32_t ModBufLen,
                              uint32_t TensorBufPtr, uint32_t TensorBufLen,
                              uint32_t TargetImgW, uint32_t TargetImgH) {
  /// Check memory instance from module.
  if (MemInst == nullptr) {
    return Unexpect(ErrCode::ExecutionFailed);
  }

  /// Input tensor and data copying
  if (Env.Inputs.size() != 1) {
    LOG(ERROR) << "ssvm_tensorflow_run_vision: Input size must be 1";
    return 1;
  }
  int64_t Dims[4] = {1, static_cast<int64_t>(TargetImgW),
                     static_cast<int64_t>(TargetImgH), 3};
  TF_Tensor *InTensor = TF_AllocateTensor(TF_FLOAT, Dims, 4, TensorBufLen);
  if (InTensor == nullptr) {
    LOG(ERROR) << "ssvm_tensorflow_run_vision: Unable to allocate input tensor";
    return 1;
  }
  std::copy_n(MemInst->getPointer<uint8_t *>(TensorBufPtr), TensorBufLen,
              static_cast<uint8_t *>(TF_TensorData(InTensor)));
  std::vector<TF_Tensor *> InTensors = {InTensor};

  /// Output tensor
  std::vector<TF_Tensor *> OutTensors(Env.Outputs.size(), nullptr);

  /// Run session
  if (!runTFSession(MemInst->getPointer<char *>(ModBufPtr), ModBufLen,
                    Env.Inputs, InTensors, Env.Outputs, OutTensors)) {
    for (auto &I : InTensors) {
      TF_DeleteTensor(I);
    }
    return 1;
  }

  /// Print results
  Env.Res.clear();
  Env.Res.str("");
  Env.Res << "[";
  for (uint32_t I = 0; I < OutTensors.size(); ++I) {
    float *OutTensorData = static_cast<float *>(TF_TensorData(OutTensors[I]));
    uint32_t NOut = TF_TensorByteSize(OutTensors[I]) / sizeof(float);
    Env.Res << "[";
    for (uint32_t J = 0; J < NOut - 1; J++) {
      Env.Res << std::fixed << std::setprecision(20) << OutTensorData[J] << ",";
    }
    Env.Res << std::fixed << std::setprecision(20) << OutTensorData[NOut - 1]
            << "]";
    if (I < OutTensors.size() - 1) {
      Env.Res << ",";
    }
  }
  Env.Res << "]";

  /// Free resources
  for (auto &I : InTensors) {
    TF_DeleteTensor(I);
  }
  for (auto &I : OutTensors) {
    TF_DeleteTensor(I);
  }
  return 0;
}

Expect<void>
SSVMTensorflowAppendInput::body(Runtime::Instance::MemoryInstance *MemInst,
                                uint32_t InputPtr, uint32_t InputLen) {
  /// Check memory instance from module.
  if (MemInst == nullptr) {
    return Unexpect(ErrCode::ExecutionFailed);
  }

  Env.Inputs.push_back(
      std::string(MemInst->getPointer<char *>(InputPtr), InputLen));
  return {};
}

Expect<void>
SSVMTensorflowAppendOutput::body(Runtime::Instance::MemoryInstance *MemInst,
                                 uint32_t OutputPtr, uint32_t OutputLen) {
  /// Check memory instance from module.
  if (MemInst == nullptr) {
    return Unexpect(ErrCode::ExecutionFailed);
  }

  Env.Outputs.push_back(
      std::string(MemInst->getPointer<char *>(OutputPtr), OutputLen));
  return {};
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
  Env.Res.clear();
  Env.Res.str("");
  return {};
}

} // namespace Host
} // namespace SSVM
