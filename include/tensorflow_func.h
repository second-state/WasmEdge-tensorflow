// SPDX-License-Identifier: Apache-2.0
#pragma once

#include "common/errcode.h"
#include "runtime/hostfunc.h"
#include "runtime/instance/memory.h"
#include "tensorflow_base.h"
#include "tensorflow_env.h"

namespace SSVM {
namespace Host {

class SSVMTensorflowLoadJPGToRGB8
    : public SSVMTensorflow<SSVMTensorflowLoadJPGToRGB8> {
public:
  SSVMTensorflowLoadJPGToRGB8(SSVMTensorflowEnvironment &Env)
      : SSVMTensorflow(Env) {}
  Expect<uint32_t> body(Runtime::Instance::MemoryInstance *MemInst,
                        uint32_t ImgBufPtr, uint32_t ImgBufLen,
                        uint32_t TargetImgW, uint32_t TargetImgH);
};

class SSVMTensorflowLoadJPGToBGR8
    : public SSVMTensorflow<SSVMTensorflowLoadJPGToBGR8> {
public:
  SSVMTensorflowLoadJPGToBGR8(SSVMTensorflowEnvironment &Env)
      : SSVMTensorflow(Env) {}
  Expect<uint32_t> body(Runtime::Instance::MemoryInstance *MemInst,
                        uint32_t ImgBufPtr, uint32_t ImgBufLen,
                        uint32_t TargetImgW, uint32_t TargetImgH);
};

class SSVMTensorflowLoadJPGToRGB32F
    : public SSVMTensorflow<SSVMTensorflowLoadJPGToRGB32F> {
public:
  SSVMTensorflowLoadJPGToRGB32F(SSVMTensorflowEnvironment &Env)
      : SSVMTensorflow(Env) {}
  Expect<uint32_t> body(Runtime::Instance::MemoryInstance *MemInst,
                        uint32_t ImgBufPtr, uint32_t ImgBufLen,
                        uint32_t TargetImgW, uint32_t TargetImgH);
};

class SSVMTensorflowLoadJPGToBGR32F
    : public SSVMTensorflow<SSVMTensorflowLoadJPGToBGR32F> {
public:
  SSVMTensorflowLoadJPGToBGR32F(SSVMTensorflowEnvironment &Env)
      : SSVMTensorflow(Env) {}
  Expect<uint32_t> body(Runtime::Instance::MemoryInstance *MemInst,
                        uint32_t ImgBufPtr, uint32_t ImgBufLen,
                        uint32_t TargetImgW, uint32_t TargetImgH);
};

class SSVMTensorflowLoadPNGToRGB8
    : public SSVMTensorflow<SSVMTensorflowLoadPNGToRGB8> {
public:
  SSVMTensorflowLoadPNGToRGB8(SSVMTensorflowEnvironment &Env)
      : SSVMTensorflow(Env) {}
  Expect<uint32_t> body(Runtime::Instance::MemoryInstance *MemInst,
                        uint32_t ImgBufPtr, uint32_t ImgBufLen,
                        uint32_t TargetImgW, uint32_t TargetImgH);
};

class SSVMTensorflowLoadPNGToBGR8
    : public SSVMTensorflow<SSVMTensorflowLoadPNGToBGR8> {
public:
  SSVMTensorflowLoadPNGToBGR8(SSVMTensorflowEnvironment &Env)
      : SSVMTensorflow(Env) {}
  Expect<uint32_t> body(Runtime::Instance::MemoryInstance *MemInst,
                        uint32_t ImgBufPtr, uint32_t ImgBufLen,
                        uint32_t TargetImgW, uint32_t TargetImgH);
};

class SSVMTensorflowLoadPNGToRGB32F
    : public SSVMTensorflow<SSVMTensorflowLoadPNGToRGB32F> {
public:
  SSVMTensorflowLoadPNGToRGB32F(SSVMTensorflowEnvironment &Env)
      : SSVMTensorflow(Env) {}
  Expect<uint32_t> body(Runtime::Instance::MemoryInstance *MemInst,
                        uint32_t ImgBufPtr, uint32_t ImgBufLen,
                        uint32_t TargetImgW, uint32_t TargetImgH);
};

class SSVMTensorflowLoadPNGToBGR32F
    : public SSVMTensorflow<SSVMTensorflowLoadPNGToBGR32F> {
public:
  SSVMTensorflowLoadPNGToBGR32F(SSVMTensorflowEnvironment &Env)
      : SSVMTensorflow(Env) {}
  Expect<uint32_t> body(Runtime::Instance::MemoryInstance *MemInst,
                        uint32_t ImgBufPtr, uint32_t ImgBufLen,
                        uint32_t TargetImgW, uint32_t TargetImgH);
};

class SSVMTensorflowRunVision : public SSVMTensorflow<SSVMTensorflowRunVision> {
public:
  SSVMTensorflowRunVision(SSVMTensorflowEnvironment &Env)
      : SSVMTensorflow(Env) {}
  Expect<uint32_t> body(Runtime::Instance::MemoryInstance *MemInst,
                        uint32_t ModBufPtr, uint32_t ModBufLen,
                        uint32_t TensorBufPtr, uint32_t TensorBufLen,
                        uint32_t TargetImgW, uint32_t TargetImgH);
};

class SSVMTensorflowAppendInput
    : public SSVMTensorflow<SSVMTensorflowAppendInput> {
public:
  SSVMTensorflowAppendInput(SSVMTensorflowEnvironment &Env)
      : SSVMTensorflow(Env) {}
  Expect<void> body(Runtime::Instance::MemoryInstance *MemInst,
                    uint32_t InputPtr, uint32_t InputLen, uint32_t DimPtr,
                    uint32_t DimCnt, uint32_t Idx);
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

class SSVMTensorflowGetResultLen
    : public SSVMTensorflow<SSVMTensorflowGetResultLen> {
public:
  SSVMTensorflowGetResultLen(SSVMTensorflowEnvironment &Env)
      : SSVMTensorflow(Env) {}
  Expect<uint32_t> body(Runtime::Instance::MemoryInstance *MemInst,
                        uint32_t Index);
};

class SSVMTensorflowGetResult : public SSVMTensorflow<SSVMTensorflowGetResult> {
public:
  SSVMTensorflowGetResult(SSVMTensorflowEnvironment &Env)
      : SSVMTensorflow(Env) {}
  Expect<void> body(Runtime::Instance::MemoryInstance *MemInst, uint32_t Index,
                    uint32_t BufPtr);
};

} // namespace Host
} // namespace SSVM