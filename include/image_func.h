// SPDX-License-Identifier: Apache-2.0
#pragma once

#include "common/errcode.h"
#include "image_base.h"
#include "image_env.h"
#include "runtime/hostfunc.h"
#include "runtime/instance/memory.h"

namespace SSVM {
namespace Host {

class SSVMImageLoadJPGToRGB8 : public SSVMImage<SSVMImageLoadJPGToRGB8> {
public:
  SSVMImageLoadJPGToRGB8(SSVMImageEnvironment &Env) : SSVMImage(Env) {}
  Expect<uint32_t> body(Runtime::Instance::MemoryInstance *MemInst,
                        uint32_t ImgBufPtr, uint32_t ImgBufLen,
                        uint32_t TargetImgW, uint32_t TargetImgH);
};

class SSVMImageLoadJPGToBGR8 : public SSVMImage<SSVMImageLoadJPGToBGR8> {
public:
  SSVMImageLoadJPGToBGR8(SSVMImageEnvironment &Env) : SSVMImage(Env) {}
  Expect<uint32_t> body(Runtime::Instance::MemoryInstance *MemInst,
                        uint32_t ImgBufPtr, uint32_t ImgBufLen,
                        uint32_t TargetImgW, uint32_t TargetImgH);
};

class SSVMImageLoadJPGToRGB32F : public SSVMImage<SSVMImageLoadJPGToRGB32F> {
public:
  SSVMImageLoadJPGToRGB32F(SSVMImageEnvironment &Env) : SSVMImage(Env) {}
  Expect<uint32_t> body(Runtime::Instance::MemoryInstance *MemInst,
                        uint32_t ImgBufPtr, uint32_t ImgBufLen,
                        uint32_t TargetImgW, uint32_t TargetImgH);
};

class SSVMImageLoadJPGToBGR32F : public SSVMImage<SSVMImageLoadJPGToBGR32F> {
public:
  SSVMImageLoadJPGToBGR32F(SSVMImageEnvironment &Env) : SSVMImage(Env) {}
  Expect<uint32_t> body(Runtime::Instance::MemoryInstance *MemInst,
                        uint32_t ImgBufPtr, uint32_t ImgBufLen,
                        uint32_t TargetImgW, uint32_t TargetImgH);
};

class SSVMImageLoadPNGToRGB8 : public SSVMImage<SSVMImageLoadPNGToRGB8> {
public:
  SSVMImageLoadPNGToRGB8(SSVMImageEnvironment &Env) : SSVMImage(Env) {}
  Expect<uint32_t> body(Runtime::Instance::MemoryInstance *MemInst,
                        uint32_t ImgBufPtr, uint32_t ImgBufLen,
                        uint32_t TargetImgW, uint32_t TargetImgH);
};

class SSVMImageLoadPNGToBGR8 : public SSVMImage<SSVMImageLoadPNGToBGR8> {
public:
  SSVMImageLoadPNGToBGR8(SSVMImageEnvironment &Env) : SSVMImage(Env) {}
  Expect<uint32_t> body(Runtime::Instance::MemoryInstance *MemInst,
                        uint32_t ImgBufPtr, uint32_t ImgBufLen,
                        uint32_t TargetImgW, uint32_t TargetImgH);
};

class SSVMImageLoadPNGToRGB32F : public SSVMImage<SSVMImageLoadPNGToRGB32F> {
public:
  SSVMImageLoadPNGToRGB32F(SSVMImageEnvironment &Env) : SSVMImage(Env) {}
  Expect<uint32_t> body(Runtime::Instance::MemoryInstance *MemInst,
                        uint32_t ImgBufPtr, uint32_t ImgBufLen,
                        uint32_t TargetImgW, uint32_t TargetImgH);
};

class SSVMImageLoadPNGToBGR32F : public SSVMImage<SSVMImageLoadPNGToBGR32F> {
public:
  SSVMImageLoadPNGToBGR32F(SSVMImageEnvironment &Env) : SSVMImage(Env) {}
  Expect<uint32_t> body(Runtime::Instance::MemoryInstance *MemInst,
                        uint32_t ImgBufPtr, uint32_t ImgBufLen,
                        uint32_t TargetImgW, uint32_t TargetImgH);
};

class SSVMImageGetResultLen : public SSVMImage<SSVMImageGetResultLen> {
public:
  SSVMImageGetResultLen(SSVMImageEnvironment &Env) : SSVMImage(Env) {}
  Expect<uint32_t> body(Runtime::Instance::MemoryInstance *MemInst);
};

class SSVMImageGetResult : public SSVMImage<SSVMImageGetResult> {
public:
  SSVMImageGetResult(SSVMImageEnvironment &Env) : SSVMImage(Env) {}
  Expect<void> body(Runtime::Instance::MemoryInstance *MemInst,
                    uint32_t BufPtr);
};

} // namespace Host
} // namespace SSVM