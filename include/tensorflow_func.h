// SPDX-License-Identifier: Apache-2.0
#pragma once

#include "common/errcode.h"
#include "runtime/hostfunc.h"
#include "runtime/instance/memory.h"
#include "tensorflow_base.h"
#include "tensorflow_env.h"

namespace SSVM {
namespace Host {

class SSVMTensorflowExecModel : public SSVMTensorflow<SSVMTensorflowExecModel> {
public:
  SSVMTensorflowExecModel(SSVMTensorflowEnvironment &Env)
      : SSVMTensorflow(Env) {}
  Expect<uint32_t> body(Runtime::Instance::MemoryInstance *MemInst,
                        uint32_t ModBufPtr, uint32_t ModBufLen,
                        uint32_t OutTensorPtr);
};

class SSVMTensorflowAllocTensor
    : public SSVMTensorflow<SSVMTensorflowAllocTensor> {
public:
  SSVMTensorflowAllocTensor(SSVMTensorflowEnvironment &Env)
      : SSVMTensorflow(Env) {}
  Expect<uint64_t> body(Runtime::Instance::MemoryInstance *MemInst,
                        uint32_t DimPtr, uint32_t DimCnt, uint32_t DataType,
                        uint32_t TensorBufPtr, uint32_t TensorBufLen);
};

class SSVMTensorflowDeleteTensor
    : public SSVMTensorflow<SSVMTensorflowDeleteTensor> {
public:
  SSVMTensorflowDeleteTensor(SSVMTensorflowEnvironment &Env)
      : SSVMTensorflow(Env) {}
  Expect<void> body(Runtime::Instance::MemoryInstance *MemInst,
                    uint64_t Tensor);
};

class SSVMTensorflowGetTensorLen
    : public SSVMTensorflow<SSVMTensorflowGetTensorLen> {
public:
  SSVMTensorflowGetTensorLen(SSVMTensorflowEnvironment &Env)
      : SSVMTensorflow(Env) {}
  Expect<uint32_t> body(Runtime::Instance::MemoryInstance *MemInst,
                        uint64_t Tensor);
};

class SSVMTensorflowGetTensorData
    : public SSVMTensorflow<SSVMTensorflowGetTensorData> {
public:
  SSVMTensorflowGetTensorData(SSVMTensorflowEnvironment &Env)
      : SSVMTensorflow(Env) {}
  Expect<void> body(Runtime::Instance::MemoryInstance *MemInst, uint64_t Tensor,
                    uint32_t BufPtr);
};

class SSVMTensorflowAppendInput
    : public SSVMTensorflow<SSVMTensorflowAppendInput> {
public:
  SSVMTensorflowAppendInput(SSVMTensorflowEnvironment &Env)
      : SSVMTensorflow(Env) {}
  Expect<void> body(Runtime::Instance::MemoryInstance *MemInst,
                    uint32_t InputPtr, uint32_t InputLen, uint32_t Idx,
                    uint64_t Tensor);
};

class SSVMTensorflowAppendOutput
    : public SSVMTensorflow<SSVMTensorflowAppendOutput> {
public:
  SSVMTensorflowAppendOutput(SSVMTensorflowEnvironment &Env)
      : SSVMTensorflow(Env) {}
  Expect<void> body(Runtime::Instance::MemoryInstance *MemInst,
                    uint32_t OutputPtr, uint32_t OutputLen, uint32_t Idx);
};

class SSVMTensorflowClearInput
    : public SSVMTensorflow<SSVMTensorflowClearInput> {
public:
  SSVMTensorflowClearInput(SSVMTensorflowEnvironment &Env)
      : SSVMTensorflow(Env) {}
  Expect<void> body(Runtime::Instance::MemoryInstance *MemInst);
};

class SSVMTensorflowClearOutput
    : public SSVMTensorflow<SSVMTensorflowClearOutput> {
public:
  SSVMTensorflowClearOutput(SSVMTensorflowEnvironment &Env)
      : SSVMTensorflow(Env) {}
  Expect<void> body(Runtime::Instance::MemoryInstance *MemInst);
};

} // namespace Host
} // namespace SSVM