// SPDX-License-Identifier: Apache-2.0
#pragma once

#include "common/errcode.h"
#include "runtime/hostfunc.h"
#include "runtime/instance/memory.h"
#include "tensorflowlite_base.h"

namespace SSVM {
namespace Host {

class SSVMTensorflowLiteCreateSession
    : public SSVMTensorflowLite<SSVMTensorflowLiteCreateSession> {
public:
  Expect<uint64_t> body(Runtime::Instance::MemoryInstance *MemInst,
                        uint32_t ModBufPtr, uint32_t ModBufLen);
};

class SSVMTensorflowLiteDeleteSession
    : public SSVMTensorflowLite<SSVMTensorflowLiteDeleteSession> {
public:
  Expect<void> body(Runtime::Instance::MemoryInstance *MemInst, uint64_t Cxt);
};

class SSVMTensorflowLiteRunSession
    : public SSVMTensorflowLite<SSVMTensorflowLiteRunSession> {
public:
  Expect<uint32_t> body(Runtime::Instance::MemoryInstance *MemInst,
                        uint64_t Cxt);
};

class SSVMTensorflowLiteGetOutputTensor
    : public SSVMTensorflowLite<SSVMTensorflowLiteGetOutputTensor> {
public:
  Expect<uint64_t> body(Runtime::Instance::MemoryInstance *MemInst,
                        uint64_t Cxt, uint32_t OutputPtr, uint32_t OutputLen);
};

class SSVMTensorflowLiteGetTensorLen
    : public SSVMTensorflowLite<SSVMTensorflowLiteGetTensorLen> {
public:
  Expect<uint32_t> body(Runtime::Instance::MemoryInstance *MemInst,
                        uint64_t Tensor);
};

class SSVMTensorflowLiteGetTensorData
    : public SSVMTensorflowLite<SSVMTensorflowLiteGetTensorData> {
public:
  Expect<void> body(Runtime::Instance::MemoryInstance *MemInst, uint64_t Tensor,
                    uint32_t BufPtr);
};

class SSVMTensorflowLiteAppendInput
    : public SSVMTensorflowLite<SSVMTensorflowLiteAppendInput> {
public:
  Expect<void> body(Runtime::Instance::MemoryInstance *MemInst, uint64_t Cxt,
                    uint32_t InputPtr, uint32_t InputLen, uint32_t TensorBufPtr,
                    uint32_t TensorBufLen);
};

} // namespace Host
} // namespace SSVM