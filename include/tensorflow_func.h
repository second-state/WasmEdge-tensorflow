// SPDX-License-Identifier: Apache-2.0
#pragma once

#include "common/errcode.h"
#include "runtime/hostfunc.h"
#include "runtime/instance/memory.h"
#include "tensorflow_base.h"
#include "tensorflow_env.h"

namespace SSVM {
namespace Host {

class SSVMTensorflowRunVision : public SSVMTensorflow<SSVMTensorflowRunVision> {
public:
  SSVMTensorflowRunVision(SSVMTensorflowEnvironment &Env)
      : SSVMTensorflow(Env) {}
  Expect<uint32_t> body(Runtime::Instance::MemoryInstance *MemInst,
                        uint32_t ModBufPtr, uint32_t ModBufLen,
                        uint32_t ImgBufPtr, uint32_t ImgBufLen,
                        uint32_t TargetImgW, uint32_t TargetImgH);
};

class SSVMTensorflowAppendInput
    : public SSVMTensorflow<SSVMTensorflowAppendInput> {
public:
  SSVMTensorflowAppendInput(SSVMTensorflowEnvironment &Env)
      : SSVMTensorflow(Env) {}
  Expect<void> body(Runtime::Instance::MemoryInstance *MemInst,
                    uint32_t InputPtr, uint32_t InputLen);
};

class SSVMTensorflowAppendOutput
    : public SSVMTensorflow<SSVMTensorflowAppendOutput> {
public:
  SSVMTensorflowAppendOutput(SSVMTensorflowEnvironment &Env)
      : SSVMTensorflow(Env) {}
  Expect<void> body(Runtime::Instance::MemoryInstance *MemInst,
                    uint32_t OutputPtr, uint32_t OutputLen);
};

class SSVMTensorflowGetResultLen
    : public SSVMTensorflow<SSVMTensorflowGetResultLen> {
public:
  SSVMTensorflowGetResultLen(SSVMTensorflowEnvironment &Env)
      : SSVMTensorflow(Env) {}
  Expect<uint32_t> body(Runtime::Instance::MemoryInstance *MemInst);
};

class SSVMTensorflowGetResult : public SSVMTensorflow<SSVMTensorflowGetResult> {
public:
  SSVMTensorflowGetResult(SSVMTensorflowEnvironment &Env)
      : SSVMTensorflow(Env) {}
  Expect<void> body(Runtime::Instance::MemoryInstance *MemInst,
                    uint32_t BufPtr);
};

} // namespace Host
} // namespace SSVM