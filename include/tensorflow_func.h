// SPDX-License-Identifier: Apache-2.0
#pragma once

#include "common/errcode.h"
#include "runtime/hostfunc.h"
#include "runtime/instance/memory.h"
#include "tensorflow_base.h"
#include "tensorflow_env.h"

namespace SSVM {
namespace Host {

class SSVMTensorflowMobilenetv2
    : public SSVMTensorflow<SSVMTensorflowMobilenetv2> {
public:
  SSVMTensorflowMobilenetv2(SSVMTensorflowEnvironment &Env)
      : SSVMTensorflow(Env) {}
  Expect<uint32_t> body(Runtime::Instance::MemoryInstance *MemInst,
                        uint32_t ModNamePtr, uint32_t ModNameLen,
                        uint32_t InputPtr, uint32_t InputLen,
                        uint32_t OutputPtr, uint32_t OutputLen,
                        uint32_t ImgNamePtr, uint32_t ImgNameLen,
                        uint32_t TargetImgW, uint32_t TargetImgH);
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