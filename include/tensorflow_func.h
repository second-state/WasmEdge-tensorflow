// SPDX-License-Identifier: Apache-2.0
#pragma once

#include "common/errcode.h"
#include "runtime/hostfunc.h"
#include "runtime/instance/memory.h"
#include "tensorflow_base.h"

namespace SSVM {
namespace Host {

class SSVMTensorflowCreateSession
    : public SSVMTensorflow<SSVMTensorflowCreateSession> {
public:
  Expect<uint64_t> body(Runtime::Instance::MemoryInstance *MemInst,
                        uint32_t ModBufPtr, uint32_t ModBufLen);
};

class SSVMTensorflowDeleteSession
    : public SSVMTensorflow<SSVMTensorflowDeleteSession> {
public:
  Expect<void> body(Runtime::Instance::MemoryInstance *MemInst, uint64_t Cxt);
};

class SSVMTensorflowRunSession
    : public SSVMTensorflow<SSVMTensorflowRunSession> {
public:
  Expect<uint32_t> body(Runtime::Instance::MemoryInstance *MemInst,
                        uint64_t Cxt);
};

class SSVMTensorflowGetOutputTensor
    : public SSVMTensorflow<SSVMTensorflowGetOutputTensor> {
public:
  Expect<uint64_t> body(Runtime::Instance::MemoryInstance *MemInst,
                        uint64_t Cxt, uint32_t OutputPtr, uint32_t OutputLen,
                        uint32_t Idx);
};

class SSVMTensorflowGetTensorLen
    : public SSVMTensorflow<SSVMTensorflowGetTensorLen> {
public:
  Expect<uint32_t> body(Runtime::Instance::MemoryInstance *MemInst,
                        uint64_t Tensor);
};

class SSVMTensorflowGetTensorData
    : public SSVMTensorflow<SSVMTensorflowGetTensorData> {
public:
  Expect<void> body(Runtime::Instance::MemoryInstance *MemInst, uint64_t Tensor,
                    uint32_t BufPtr);
};

class SSVMTensorflowAppendInput
    : public SSVMTensorflow<SSVMTensorflowAppendInput> {
public:
  Expect<void> body(Runtime::Instance::MemoryInstance *MemInst, uint64_t Cxt,
                    uint32_t InputPtr, uint32_t InputLen, uint32_t Idx,
                    uint32_t DimPtr, uint32_t DimCnt, uint32_t DataType,
                    uint32_t TensorBufPtr, uint32_t TensorBufLen);
};

class SSVMTensorflowAppendOutput
    : public SSVMTensorflow<SSVMTensorflowAppendOutput> {
public:
  Expect<void> body(Runtime::Instance::MemoryInstance *MemInst, uint64_t Cxt,
                    uint32_t OutputPtr, uint32_t OutputLen, uint32_t Idx);
};

class SSVMTensorflowClearInput
    : public SSVMTensorflow<SSVMTensorflowClearInput> {
public:
  Expect<void> body(Runtime::Instance::MemoryInstance *MemInst, uint64_t Cxt);
};

class SSVMTensorflowClearOutput
    : public SSVMTensorflow<SSVMTensorflowClearOutput> {
public:
  Expect<void> body(Runtime::Instance::MemoryInstance *MemInst, uint64_t Cxt);
};

} // namespace Host
} // namespace SSVM