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
    LOG(ERROR) << e.what();
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
                  Span<const std::pair<std::string, uint32_t>> InputNames,
                  std::vector<TF_Tensor *> &InTensor,
                  Span<const std::pair<std::string, uint32_t>> OutputNames,
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
        TF_Output{TF_GraphOperationByName(Graph, S.first.c_str()),
                  static_cast<int>(S.second)});
  }
  std::vector<TF_Output> Outputs;
  for (auto &S : OutputNames) {
    Outputs.emplace_back(
        TF_Output{TF_GraphOperationByName(Graph, S.first.c_str()),
                  static_cast<int>(S.second)});
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
  Env.Res = resizeImg(Img, TargetImgW, TargetImgH);
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
  Env.Res = resizeImg(Img, TargetImgW, TargetImgH);
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
  uint8_t *Start = reinterpret_cast<uint8_t *>(&Flat[0]);
  Env.Res = std::vector<uint8_t>(Start, Start + sizeof(float) * Flat.size());
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
  uint8_t *Start = reinterpret_cast<uint8_t *>(&Flat[0]);
  Env.Res = std::vector<uint8_t>(Start, Start + sizeof(float) * Flat.size());
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
  Env.Res = resizeImg(Img, TargetImgW, TargetImgH);
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
  Env.Res = resizeImg(Img, TargetImgW, TargetImgH);
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
  uint8_t *Start = reinterpret_cast<uint8_t *>(&Flat[0]);
  Env.Res = std::vector<uint8_t>(Start, Start + sizeof(float) * Flat.size());
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
  uint8_t *Start = reinterpret_cast<uint8_t *>(&Flat[0]);
  Env.Res = std::vector<uint8_t>(Start, Start + sizeof(float) * Flat.size());
  return 0;
}

Expect<uint32_t>
SSVMTensorflowExecModel::body(Runtime::Instance::MemoryInstance *MemInst,
                              uint32_t ModBufPtr, uint32_t ModBufLen,
                              uint32_t OutTensorPtr) {
  /// Check memory instance from module.
  if (MemInst == nullptr) {
    return Unexpect(ErrCode::ExecutionFailed);
  }

  /// Output tensor
  std::vector<TF_Tensor *> OutTensors(Env.Outputs.size(), nullptr);

  /// Run session
  if (!runTFSession(MemInst->getPointer<char *>(ModBufPtr), ModBufLen,
                    Env.Inputs, Env.InputTensors, Env.Outputs, OutTensors)) {
    return 1;
  }

  /// Store output tensors
  std::copy_n(OutTensors.begin(), Env.Outputs.size(),
              MemInst->getPointer<TF_Tensor **>(OutTensorPtr));
  return 0;
}

Expect<uint64_t>
SSVMTensorflowAllocTensor::body(Runtime::Instance::MemoryInstance *MemInst,
                                uint32_t DimPtr, uint32_t DimCnt,
                                uint32_t DataType, uint32_t TensorBufPtr,
                                uint32_t TensorBufLen) {
  /// Check memory instance from module.
  if (MemInst == nullptr) {
    return Unexpect(ErrCode::ExecutionFailed);
  }

  /// Allocate tensor and data copying
  TF_Tensor *Tensor = nullptr;
  if (DimCnt > 0) {
    Tensor = TF_AllocateTensor(static_cast<TF_DataType>(DataType),
                               MemInst->getPointer<int64_t *>(DimPtr), DimCnt,
                               TensorBufLen);
  } else {
    Tensor = TF_AllocateTensor(static_cast<TF_DataType>(DataType), nullptr, 0,
                               TensorBufLen);
  }
  if (Tensor != nullptr) {
    std::copy_n(MemInst->getPointer<uint8_t *>(TensorBufPtr), TensorBufLen,
                static_cast<uint8_t *>(TF_TensorData(Tensor)));
  }
  return static_cast<uint64_t>(reinterpret_cast<std::uintptr_t>(Tensor));
}

Expect<void>
SSVMTensorflowDeleteTensor::body(Runtime::Instance::MemoryInstance *MemInst,
                                 uint64_t Tensor) {
  TF_Tensor *T = reinterpret_cast<TF_Tensor *>(Tensor);
  if (T != nullptr) {
    TF_DeleteTensor(T);
  }
  return {};
}

Expect<uint32_t>
SSVMTensorflowGetTensorLen::body(Runtime::Instance::MemoryInstance *MemInst,
                                 uint64_t Tensor) {
  TF_Tensor *T = reinterpret_cast<TF_Tensor *>(Tensor);
  if (T != nullptr) {
    return TF_TensorByteSize(T);
  }
  return 0;
}

Expect<void>
SSVMTensorflowGetTensorData::body(Runtime::Instance::MemoryInstance *MemInst,
                                  uint64_t Tensor, uint32_t BufPtr) {
  TF_Tensor *T = reinterpret_cast<TF_Tensor *>(Tensor);
  if (T != nullptr) {
    uint8_t *Data = static_cast<uint8_t *>(TF_TensorData(T));
    uint8_t *Buf = MemInst->getPointer<uint8_t *>(BufPtr);
    if (TF_TensorByteSize(T) > 0) {
      std::copy_n(Data, TF_TensorByteSize(T), Buf);
    }
  }
  return {};
}

Expect<void>
SSVMTensorflowAppendInput::body(Runtime::Instance::MemoryInstance *MemInst,
                                uint32_t InputPtr, uint32_t InputLen,
                                uint32_t Idx, uint64_t Tensor) {
  /// Check memory instance from module.
  if (MemInst == nullptr) {
    return Unexpect(ErrCode::ExecutionFailed);
  }

  Env.Inputs.push_back(
      {std::string(MemInst->getPointer<char *>(InputPtr), InputLen), Idx});
  Env.InputTensors.push_back(reinterpret_cast<TF_Tensor *>(Tensor));
  return {};
}

Expect<void>
SSVMTensorflowAppendOutput::body(Runtime::Instance::MemoryInstance *MemInst,
                                 uint32_t OutputPtr, uint32_t OutputLen,
                                 uint32_t Idx) {
  /// Check memory instance from module.
  if (MemInst == nullptr) {
    return Unexpect(ErrCode::ExecutionFailed);
  }

  Env.Outputs.push_back(
      {std::string(MemInst->getPointer<char *>(OutputPtr), OutputLen), Idx});
  return {};
}

Expect<void>
SSVMTensorflowClearInput::body(Runtime::Instance::MemoryInstance *MemInst) {
  Env.Inputs.clear();
  Env.InputTensors.clear();
  return {};
}

Expect<void>
SSVMTensorflowClearOutput::body(Runtime::Instance::MemoryInstance *MemInst) {
  Env.Outputs.clear();
  return {};
}

Expect<uint32_t>
SSVMTensorflowGetResultLen::body(Runtime::Instance::MemoryInstance *MemInst) {
  return Env.Res.size();
}

Expect<void>
SSVMTensorflowGetResult::body(Runtime::Instance::MemoryInstance *MemInst,
                              uint32_t BufPtr) {
  /// Check memory instance from module.
  if (MemInst == nullptr) {
    return Unexpect(ErrCode::ExecutionFailed);
  }

  uint8_t *Buf = MemInst->getPointer<uint8_t *>(BufPtr);
  if (Env.Res.size() > 0) {
    std::copy_n(Env.Res.begin(), Env.Res.size(), Buf);
  }
  return {};
}

} // namespace Host
} // namespace SSVM
