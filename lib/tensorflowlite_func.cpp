// SPDX-License-Identifier: Apache-2.0
#include <string>
#include <vector>

#include "tensorflow/lite/c/c_api.h"

#include "common/log.h"
#include "common/span.h"
#include "tensorflowlite_func.h"

namespace WasmEdge {
namespace Host {

Expect<uint64_t> WasmEdgeTensorflowLiteCreateSession::body(
    Runtime::Instance::MemoryInstance *MemInst, uint32_t ModBufPtr,
    uint32_t ModBufLen) {
  /// Check memory instance from module.
  if (MemInst == nullptr) {
    return Unexpect(ErrCode::ExecutionFailed);
  }

  /// Create context and import graph.
  struct WasmEdgeTensorflowLiteContext *Cxt =
      new WasmEdgeTensorflowLiteContext();
  auto *Model =
      TfLiteModelCreate(MemInst->getPointer<char *>(ModBufPtr), ModBufLen);
  if (Model == nullptr) {
    LOG(ERROR) << "wasmedge_tensorflowlite_create_session: Cannot import "
                  "TFLite model.";
    return 0;
  }
  auto *Ops = TfLiteInterpreterOptionsCreate();
  TfLiteInterpreterOptionsSetNumThreads(Ops, 2);
  Cxt->Interp = TfLiteInterpreterCreate(Model, Ops);
  TfLiteInterpreterOptionsDelete(Ops);
  TfLiteModelDelete(Model);
  if (Cxt->Interp == nullptr) {
    LOG(ERROR)
        << "wasmedge_tensorflowlite_create_session: Cannot create TFLite "
           "interpreter.";
    return 0;
  }
  TfLiteInterpreterAllocateTensors(Cxt->Interp);
  return static_cast<uint64_t>(reinterpret_cast<std::uintptr_t>(Cxt));
}

Expect<void> WasmEdgeTensorflowLiteDeleteSession::body(
    Runtime::Instance::MemoryInstance *MemInst, uint64_t Cxt) {
  /// Context struct
  auto *C = reinterpret_cast<struct WasmEdgeTensorflowLiteContext *>(Cxt);
  if (C != nullptr) {
    delete C;
  }
  return {};
}

Expect<uint32_t> WasmEdgeTensorflowLiteRunSession::body(
    Runtime::Instance::MemoryInstance *MemInst, uint64_t Cxt) {
  /// Context struct
  auto *C = reinterpret_cast<struct WasmEdgeTensorflowLiteContext *>(Cxt);

  /// Run session
  TfLiteStatus Stat = TfLiteInterpreterInvoke(C->Interp);
  if (Stat != TfLiteStatus::kTfLiteOk) {
    LOG(ERROR) << "wasmedge_tensorflowlite_run_session: Invokation failed.";
    return 1;
  }
  return 0;
}

Expect<uint64_t> WasmEdgeTensorflowLiteGetOutputTensor::body(
    Runtime::Instance::MemoryInstance *MemInst, uint64_t Cxt,
    uint32_t OutputPtr, uint32_t OutputLen) {
  /// Check memory instance from module.
  if (MemInst == nullptr) {
    return Unexpect(ErrCode::ExecutionFailed);
  }

  /// Context struct
  auto *C = reinterpret_cast<struct WasmEdgeTensorflowLiteContext *>(Cxt);

  /// Find the output tensor
  std::string Name(MemInst->getPointer<char *>(OutputPtr), OutputLen);
  uint32_t OutCnt = TfLiteInterpreterGetOutputTensorCount(C->Interp);

  for (uint32_t I = 0; I < OutCnt; ++I) {
    const TfLiteTensor *T = TfLiteInterpreterGetOutputTensor(C->Interp, I);
    if (Name == std::string(TfLiteTensorName(T))) {
      return static_cast<uint64_t>(reinterpret_cast<std::uintptr_t>(T));
    }
  }
  return 0;
}

Expect<uint32_t> WasmEdgeTensorflowLiteGetTensorLen::body(
    Runtime::Instance::MemoryInstance *MemInst, uint64_t Tensor) {
  /// Return tensor data length.
  TfLiteTensor *T = reinterpret_cast<TfLiteTensor *>(Tensor);
  if (T != nullptr) {
    return TfLiteTensorByteSize(T);
  }
  return 0;
}

Expect<void> WasmEdgeTensorflowLiteGetTensorData::body(
    Runtime::Instance::MemoryInstance *MemInst, uint64_t Tensor,
    uint32_t BufPtr) {
  /// Check memory instance from module.
  if (MemInst == nullptr) {
    return Unexpect(ErrCode::ExecutionFailed);
  }

  /// Copy tensor data to buffer.
  TfLiteTensor *T = reinterpret_cast<TfLiteTensor *>(Tensor);
  if (T != nullptr) {
    uint8_t *Buf = MemInst->getPointer<uint8_t *>(BufPtr);
    if (TfLiteTensorByteSize(T) > 0) {
      TfLiteTensorCopyToBuffer(T, Buf, TfLiteTensorByteSize(T));
    }
  }
  return {};
}

Expect<void> WasmEdgeTensorflowLiteAppendInput::body(
    Runtime::Instance::MemoryInstance *MemInst, uint64_t Cxt, uint32_t InputPtr,
    uint32_t InputLen, uint32_t TensorBufPtr, uint32_t TensorBufLen) {
  /// Check memory instance from module.
  if (MemInst == nullptr) {
    return Unexpect(ErrCode::ExecutionFailed);
  }

  /// Context struct
  auto *C = reinterpret_cast<struct WasmEdgeTensorflowLiteContext *>(Cxt);

  /// Find the input tensor
  std::string Name(MemInst->getPointer<char *>(InputPtr), InputLen);
  uint32_t InCnt = TfLiteInterpreterGetInputTensorCount(C->Interp);

  for (uint32_t I = 0; I < InCnt; ++I) {
    auto *T = TfLiteInterpreterGetInputTensor(C->Interp, I);
    if (Name == std::string(TfLiteTensorName(T))) {
      TfLiteTensorCopyFromBuffer(
          T, MemInst->getPointer<uint8_t *>(TensorBufPtr), TensorBufLen);
      break;
    }
  }
  return {};
}

} // namespace Host
} // namespace WasmEdge
