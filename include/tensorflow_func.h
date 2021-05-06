// SPDX-License-Identifier: Apache-2.0
#pragma once

#include "common/errcode.h"
#include "runtime/hostfunc.h"
#include "runtime/instance/memory.h"
#include "tensorflow_base.h"

namespace WasmEdge {
namespace Host {

class WasmEdgeTensorflowCreateSession
    : public WasmEdgeTensorflow<WasmEdgeTensorflowCreateSession> {
public:
  Expect<uint64_t> body(Runtime::Instance::MemoryInstance *MemInst,
                        uint32_t ModBufPtr, uint32_t ModBufLen);
};

class WasmEdgeTensorflowDeleteSession
    : public WasmEdgeTensorflow<WasmEdgeTensorflowDeleteSession> {
public:
  Expect<void> body(Runtime::Instance::MemoryInstance *MemInst, uint64_t Cxt);
};

class WasmEdgeTensorflowRunSession
    : public WasmEdgeTensorflow<WasmEdgeTensorflowRunSession> {
public:
  Expect<uint32_t> body(Runtime::Instance::MemoryInstance *MemInst,
                        uint64_t Cxt);
};

class WasmEdgeTensorflowGetOutputTensor
    : public WasmEdgeTensorflow<WasmEdgeTensorflowGetOutputTensor> {
public:
  Expect<uint64_t> body(Runtime::Instance::MemoryInstance *MemInst,
                        uint64_t Cxt, uint32_t OutputPtr, uint32_t OutputLen,
                        uint32_t Idx);
};

class WasmEdgeTensorflowGetTensorLen
    : public WasmEdgeTensorflow<WasmEdgeTensorflowGetTensorLen> {
public:
  Expect<uint32_t> body(Runtime::Instance::MemoryInstance *MemInst,
                        uint64_t Tensor);
};

class WasmEdgeTensorflowGetTensorData
    : public WasmEdgeTensorflow<WasmEdgeTensorflowGetTensorData> {
public:
  Expect<void> body(Runtime::Instance::MemoryInstance *MemInst, uint64_t Tensor,
                    uint32_t BufPtr);
};

class WasmEdgeTensorflowAppendInput
    : public WasmEdgeTensorflow<WasmEdgeTensorflowAppendInput> {
public:
  Expect<void> body(Runtime::Instance::MemoryInstance *MemInst, uint64_t Cxt,
                    uint32_t InputPtr, uint32_t InputLen, uint32_t Idx,
                    uint32_t DimPtr, uint32_t DimCnt, uint32_t DataType,
                    uint32_t TensorBufPtr, uint32_t TensorBufLen);
};

class WasmEdgeTensorflowAppendOutput
    : public WasmEdgeTensorflow<WasmEdgeTensorflowAppendOutput> {
public:
  Expect<void> body(Runtime::Instance::MemoryInstance *MemInst, uint64_t Cxt,
                    uint32_t OutputPtr, uint32_t OutputLen, uint32_t Idx);
};

class WasmEdgeTensorflowClearInput
    : public WasmEdgeTensorflow<WasmEdgeTensorflowClearInput> {
public:
  Expect<void> body(Runtime::Instance::MemoryInstance *MemInst, uint64_t Cxt);
};

class WasmEdgeTensorflowClearOutput
    : public WasmEdgeTensorflow<WasmEdgeTensorflowClearOutput> {
public:
  Expect<void> body(Runtime::Instance::MemoryInstance *MemInst, uint64_t Cxt);
};

} // namespace Host
} // namespace WasmEdge