// SPDX-License-Identifier: Apache-2.0
#include <string>
#include <vector>

#include "tensorflow/c/c_api.h"

#include "common/log.h"
#include "common/span.h"
#include "tensorflow_func.h"

namespace WasmEdge {
namespace Host {

Expect<uint64_t> WasmEdgeTensorflowCreateSession::body(
    Runtime::Instance::MemoryInstance *MemInst, uint32_t ModBufPtr,
    uint32_t ModBufLen) {
  /// Check memory instance from module.
  if (MemInst == nullptr) {
    return Unexpect(ErrCode::ExecutionFailed);
  }

  /// Create context and import graph.
  struct WasmEdgeTensorflowContext *Cxt = new WasmEdgeTensorflowContext();
  Cxt->Graph = TF_NewGraph();
  Cxt->Buffer =
      TF_NewBufferFromString(MemInst->getPointer<char *>(ModBufPtr), ModBufLen);
  Cxt->GraphOpts = TF_NewImportGraphDefOptions();
  TF_GraphImportGraphDef(Cxt->Graph, Cxt->Buffer, Cxt->GraphOpts, Cxt->Stat);
  if (TF_GetCode(Cxt->Stat) != TF_OK) {
    LOG(ERROR) << "wasmedge_tensorflow_create_session: Cannot import graph: "
               << TF_Message(Cxt->Stat);
    delete Cxt;
    return 0;
  }

  /// Create session.
  Cxt->SessionOpts = TF_NewSessionOptions();
  Cxt->Session = TF_NewSession(Cxt->Graph, Cxt->SessionOpts, Cxt->Stat);
  if (TF_GetCode(Cxt->Stat) != TF_OK) {
    LOG(ERROR)
        << "wasmedge_tensorflow_create_session: Unable to create session: "
        << TF_Message(Cxt->Stat);
    delete Cxt;
    return 0;
  }
  return static_cast<uint64_t>(reinterpret_cast<std::uintptr_t>(Cxt));
}

Expect<void> WasmEdgeTensorflowDeleteSession::body(
    Runtime::Instance::MemoryInstance *MemInst, uint64_t Cxt) {
  /// Context struct
  auto *C = reinterpret_cast<struct WasmEdgeTensorflowContext *>(Cxt);
  if (C != nullptr) {
    delete C;
  }
  return {};
}

Expect<uint32_t>
WasmEdgeTensorflowRunSession::body(Runtime::Instance::MemoryInstance *MemInst,
                                   uint64_t Cxt) {
  /// Context struct
  auto *C = reinterpret_cast<struct WasmEdgeTensorflowContext *>(Cxt);

  /// Delete old output tensors
  for (auto T : C->OutputTensors) {
    if (T) {
      TF_DeleteTensor(T);
    }
  }

  /// Run session
  TF_SessionRun(C->Session,
                // RunOptions
                nullptr,
                // Input tensors
                &(C->Inputs[0]), &(C->InputTensors[0]), C->Inputs.size(),
                // Output tensors
                &(C->Outputs[0]), &(C->OutputTensors[0]), C->Outputs.size(),
                // Target operations
                nullptr, 0,
                // RunMetadata
                nullptr,
                // Output status
                C->Stat);

  if (TF_GetCode(C->Stat) != TF_OK) {
    LOG(ERROR) << "wasmedge_tensorflow_run_session: Unable to run session: "
               << TF_Message(C->Stat);
    return 1;
  }
  return 0;
}

Expect<uint64_t> WasmEdgeTensorflowGetOutputTensor::body(
    Runtime::Instance::MemoryInstance *MemInst, uint64_t Cxt,
    uint32_t OutputPtr, uint32_t OutputLen, uint32_t Idx) {
  /// Check memory instance from module.
  if (MemInst == nullptr) {
    return Unexpect(ErrCode::ExecutionFailed);
  }

  /// Context struct
  auto *C = reinterpret_cast<struct WasmEdgeTensorflowContext *>(Cxt);

  /// Find the output tensor
  std::string Name(MemInst->getPointer<char *>(OutputPtr), OutputLen);
  for (uint32_t I = 0; I < C->OutputNames.size(); ++I) {
    if (Name == C->OutputNames[I].first && Idx == C->OutputNames[I].second) {
      return static_cast<uint64_t>(
          reinterpret_cast<std::uintptr_t>(C->OutputTensors[I]));
    }
  }
  return 0;
}

Expect<uint32_t>
WasmEdgeTensorflowGetTensorLen::body(Runtime::Instance::MemoryInstance *MemInst,
                                     uint64_t Tensor) {
  /// Return tensor data length.
  TF_Tensor *T = reinterpret_cast<TF_Tensor *>(Tensor);
  if (T != nullptr) {
    return TF_TensorByteSize(T);
  }
  return 0;
}

Expect<void> WasmEdgeTensorflowGetTensorData::body(
    Runtime::Instance::MemoryInstance *MemInst, uint64_t Tensor,
    uint32_t BufPtr) {
  /// Check memory instance from module.
  if (MemInst == nullptr) {
    return Unexpect(ErrCode::ExecutionFailed);
  }

  /// Copy tensor data to buffer.
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

Expect<void> WasmEdgeTensorflowAppendInput::body(
    Runtime::Instance::MemoryInstance *MemInst, uint64_t Cxt, uint32_t InputPtr,
    uint32_t InputLen, uint32_t Idx, uint32_t DimPtr, uint32_t DimCnt,
    uint32_t DataType, uint32_t TensorBufPtr, uint32_t TensorBufLen) {
  /// Check memory instance from module.
  if (MemInst == nullptr) {
    return Unexpect(ErrCode::ExecutionFailed);
  }

  /// Context struct
  auto *C = reinterpret_cast<struct WasmEdgeTensorflowContext *>(Cxt);

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
  C->InputTensors.push_back(Tensor);

  /// Store names and operations
  std::string Name(MemInst->getPointer<char *>(InputPtr), InputLen);
  C->InputNames.push_back({Name, Idx});
  C->Inputs.emplace_back(TF_Output{
      TF_GraphOperationByName(C->Graph, Name.c_str()), static_cast<int>(Idx)});
  return {};
}

Expect<void>
WasmEdgeTensorflowAppendOutput::body(Runtime::Instance::MemoryInstance *MemInst,
                                     uint64_t Cxt, uint32_t OutputPtr,
                                     uint32_t OutputLen, uint32_t Idx) {
  /// Check memory instance from module.
  if (MemInst == nullptr) {
    return Unexpect(ErrCode::ExecutionFailed);
  }

  /// Context struct
  auto *C = reinterpret_cast<struct WasmEdgeTensorflowContext *>(Cxt);
  std::string Name(MemInst->getPointer<char *>(OutputPtr), OutputLen);
  C->OutputTensors.push_back(nullptr);

  /// Store names and operations
  C->OutputNames.push_back({Name, Idx});
  C->Outputs.emplace_back(TF_Output{
      TF_GraphOperationByName(C->Graph, Name.c_str()), static_cast<int>(Idx)});
  return {};
}

Expect<void>
WasmEdgeTensorflowClearInput::body(Runtime::Instance::MemoryInstance *MemInst,
                                   uint64_t Cxt) {
  auto *C = reinterpret_cast<struct WasmEdgeTensorflowContext *>(Cxt);
  C->Inputs.clear();
  C->InputNames.clear();
  for (auto T : C->InputTensors) {
    if (T) {
      TF_DeleteTensor(T);
    }
  }
  C->InputTensors.clear();
  return {};
}

Expect<void>
WasmEdgeTensorflowClearOutput::body(Runtime::Instance::MemoryInstance *MemInst,
                                    uint64_t Cxt) {
  auto *C = reinterpret_cast<struct WasmEdgeTensorflowContext *>(Cxt);
  C->Outputs.clear();
  C->OutputNames.clear();
  for (auto T : C->OutputTensors) {
    if (T) {
      TF_DeleteTensor(T);
    }
  }
  C->OutputTensors.clear();
  return {};
}

} // namespace Host
} // namespace WasmEdge
