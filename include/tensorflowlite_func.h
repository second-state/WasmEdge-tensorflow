// SPDX-License-Identifier: Apache-2.0
#pragma once

#include "common/errcode.h"
#include "runtime/hostfunc.h"
#include "runtime/instance/memory.h"
#include "tensorflowlite_base.h"

namespace WasmEdge {
namespace Host {

class WasmEdgeTensorflowLiteCreateSession
    : public WasmEdgeTensorflowLite<WasmEdgeTensorflowLiteCreateSession> {
public:
  Expect<uint64_t> body(Runtime::Instance::MemoryInstance *MemInst,
                        uint32_t ModBufPtr, uint32_t ModBufLen);
};

class WasmEdgeTensorflowLiteDeleteSession
    : public WasmEdgeTensorflowLite<WasmEdgeTensorflowLiteDeleteSession> {
public:
  Expect<void> body(Runtime::Instance::MemoryInstance *MemInst, uint64_t Cxt);
};

class WasmEdgeTensorflowLiteRunSession
    : public WasmEdgeTensorflowLite<WasmEdgeTensorflowLiteRunSession> {
public:
  Expect<uint32_t> body(Runtime::Instance::MemoryInstance *MemInst,
                        uint64_t Cxt);
};

class WasmEdgeTensorflowLiteGetOutputTensor
    : public WasmEdgeTensorflowLite<WasmEdgeTensorflowLiteGetOutputTensor> {
public:
  Expect<uint64_t> body(Runtime::Instance::MemoryInstance *MemInst,
                        uint64_t Cxt, uint32_t OutputPtr, uint32_t OutputLen);
};

class WasmEdgeTensorflowLiteGetTensorLen
    : public WasmEdgeTensorflowLite<WasmEdgeTensorflowLiteGetTensorLen> {
public:
  Expect<uint32_t> body(Runtime::Instance::MemoryInstance *MemInst,
                        uint64_t Tensor);
};

class WasmEdgeTensorflowLiteGetTensorData
    : public WasmEdgeTensorflowLite<WasmEdgeTensorflowLiteGetTensorData> {
public:
  Expect<void> body(Runtime::Instance::MemoryInstance *MemInst, uint64_t Tensor,
                    uint32_t BufPtr);
};

class WasmEdgeTensorflowLiteAppendInput
    : public WasmEdgeTensorflowLite<WasmEdgeTensorflowLiteAppendInput> {
public:
  Expect<void> body(Runtime::Instance::MemoryInstance *MemInst, uint64_t Cxt,
                    uint32_t InputPtr, uint32_t InputLen, uint32_t TensorBufPtr,
                    uint32_t TensorBufLen);
};

} // namespace Host
} // namespace WasmEdge