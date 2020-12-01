// SPDX-License-Identifier: Apache-2.0
#pragma once

#include "common/errcode.h"
#include "runtime/hostfunc.h"
#include "runtime/instance/memory.h"

namespace SSVM {
namespace Host {

template <typename T>
class SSVMTensorflowFake : public Runtime::HostFunction<T> {
public:
  SSVMTensorflowFake() : Runtime::HostFunction<T>(0) {}
};

class SSVMTensorflowFakeCreateSession
    : public SSVMTensorflowFake<SSVMTensorflowFakeCreateSession> {
public:
  Expect<uint64_t> body(Runtime::Instance::MemoryInstance *MemInst,
                        uint32_t ModBufPtr, uint32_t ModBufLen) {
    return 0;
  }
};

class SSVMTensorflowFakeDeleteSession
    : public SSVMTensorflowFake<SSVMTensorflowFakeDeleteSession> {
public:
  Expect<void> body(Runtime::Instance::MemoryInstance *MemInst, uint64_t Cxt) {
    return {};
  }
};

class SSVMTensorflowFakeRunSession
    : public SSVMTensorflowFake<SSVMTensorflowFakeRunSession> {
public:
  Expect<uint32_t> body(Runtime::Instance::MemoryInstance *MemInst,
                        uint64_t Cxt) {
    return 0;
  }
};

class SSVMTensorflowFakeGetOutputTensor
    : public SSVMTensorflowFake<SSVMTensorflowFakeGetOutputTensor> {
public:
  Expect<uint64_t> body(Runtime::Instance::MemoryInstance *MemInst,
                        uint64_t Cxt, uint32_t OutputPtr, uint32_t OutputLen,
                        uint32_t Idx) {
    return 0;
  }
};

class SSVMTensorflowFakeGetTensorLen
    : public SSVMTensorflowFake<SSVMTensorflowFakeGetTensorLen> {
public:
  Expect<uint32_t> body(Runtime::Instance::MemoryInstance *MemInst,
                        uint64_t Tensor) {
    return 0;
  }
};

class SSVMTensorflowFakeGetTensorData
    : public SSVMTensorflowFake<SSVMTensorflowFakeGetTensorData> {
public:
  Expect<void> body(Runtime::Instance::MemoryInstance *MemInst, uint64_t Tensor,
                    uint32_t BufPtr) {
    return {};
  }
};

class SSVMTensorflowFakeAppendInput
    : public SSVMTensorflowFake<SSVMTensorflowFakeAppendInput> {
public:
  Expect<void> body(Runtime::Instance::MemoryInstance *MemInst, uint64_t Cxt,
                    uint32_t InputPtr, uint32_t InputLen, uint32_t Idx,
                    uint32_t DimPtr, uint32_t DimCnt, uint32_t DataType,
                    uint32_t TensorBufPtr, uint32_t TensorBufLen) {
    return {};
  }
};

class SSVMTensorflowFakeAppendOutput
    : public SSVMTensorflowFake<SSVMTensorflowFakeAppendOutput> {
public:
  Expect<void> body(Runtime::Instance::MemoryInstance *MemInst, uint64_t Cxt,
                    uint32_t OutputPtr, uint32_t OutputLen, uint32_t Idx) {
    return {};
  }
};

class SSVMTensorflowFakeClearInput
    : public SSVMTensorflowFake<SSVMTensorflowFakeClearInput> {
public:
  Expect<void> body(Runtime::Instance::MemoryInstance *MemInst, uint64_t Cxt) {
    return {};
  }
};

class SSVMTensorflowFakeClearOutput
    : public SSVMTensorflowFake<SSVMTensorflowFakeClearOutput> {
public:
  Expect<void> body(Runtime::Instance::MemoryInstance *MemInst, uint64_t Cxt) {
    return {};
  }
};

} // namespace Host
} // namespace SSVM