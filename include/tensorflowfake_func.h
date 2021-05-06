// SPDX-License-Identifier: Apache-2.0
#pragma once

#include "common/errcode.h"
#include "runtime/hostfunc.h"
#include "runtime/instance/memory.h"

namespace WasmEdge {
namespace Host {

template <typename T>
class WasmEdgeTensorflowFake : public Runtime::HostFunction<T> {
public:
  WasmEdgeTensorflowFake() : Runtime::HostFunction<T>(0) {}
};

class WasmEdgeTensorflowFakeCreateSession
    : public WasmEdgeTensorflowFake<WasmEdgeTensorflowFakeCreateSession> {
public:
  Expect<uint64_t> body(Runtime::Instance::MemoryInstance *MemInst,
                        uint32_t ModBufPtr, uint32_t ModBufLen) {
    return 0;
  }
};

class WasmEdgeTensorflowFakeDeleteSession
    : public WasmEdgeTensorflowFake<WasmEdgeTensorflowFakeDeleteSession> {
public:
  Expect<void> body(Runtime::Instance::MemoryInstance *MemInst, uint64_t Cxt) {
    return {};
  }
};

class WasmEdgeTensorflowFakeRunSession
    : public WasmEdgeTensorflowFake<WasmEdgeTensorflowFakeRunSession> {
public:
  Expect<uint32_t> body(Runtime::Instance::MemoryInstance *MemInst,
                        uint64_t Cxt) {
    return 0;
  }
};

class WasmEdgeTensorflowFakeGetOutputTensor
    : public WasmEdgeTensorflowFake<WasmEdgeTensorflowFakeGetOutputTensor> {
public:
  Expect<uint64_t> body(Runtime::Instance::MemoryInstance *MemInst,
                        uint64_t Cxt, uint32_t OutputPtr, uint32_t OutputLen,
                        uint32_t Idx) {
    return 0;
  }
};

class WasmEdgeTensorflowFakeGetTensorLen
    : public WasmEdgeTensorflowFake<WasmEdgeTensorflowFakeGetTensorLen> {
public:
  Expect<uint32_t> body(Runtime::Instance::MemoryInstance *MemInst,
                        uint64_t Tensor) {
    return 0;
  }
};

class WasmEdgeTensorflowFakeGetTensorData
    : public WasmEdgeTensorflowFake<WasmEdgeTensorflowFakeGetTensorData> {
public:
  Expect<void> body(Runtime::Instance::MemoryInstance *MemInst, uint64_t Tensor,
                    uint32_t BufPtr) {
    return {};
  }
};

class WasmEdgeTensorflowFakeAppendInput
    : public WasmEdgeTensorflowFake<WasmEdgeTensorflowFakeAppendInput> {
public:
  Expect<void> body(Runtime::Instance::MemoryInstance *MemInst, uint64_t Cxt,
                    uint32_t InputPtr, uint32_t InputLen, uint32_t Idx,
                    uint32_t DimPtr, uint32_t DimCnt, uint32_t DataType,
                    uint32_t TensorBufPtr, uint32_t TensorBufLen) {
    return {};
  }
};

class WasmEdgeTensorflowFakeAppendOutput
    : public WasmEdgeTensorflowFake<WasmEdgeTensorflowFakeAppendOutput> {
public:
  Expect<void> body(Runtime::Instance::MemoryInstance *MemInst, uint64_t Cxt,
                    uint32_t OutputPtr, uint32_t OutputLen, uint32_t Idx) {
    return {};
  }
};

class WasmEdgeTensorflowFakeClearInput
    : public WasmEdgeTensorflowFake<WasmEdgeTensorflowFakeClearInput> {
public:
  Expect<void> body(Runtime::Instance::MemoryInstance *MemInst, uint64_t Cxt) {
    return {};
  }
};

class WasmEdgeTensorflowFakeClearOutput
    : public WasmEdgeTensorflowFake<WasmEdgeTensorflowFakeClearOutput> {
public:
  Expect<void> body(Runtime::Instance::MemoryInstance *MemInst, uint64_t Cxt) {
    return {};
  }
};

} // namespace Host
} // namespace WasmEdge