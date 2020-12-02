// SPDX-License-Identifier: Apache-2.0
#pragma once

#include "common/errcode.h"
#include "image_base.h"
#include "runtime/hostfunc.h"
#include "runtime/instance/memory.h"

namespace SSVM {
namespace Host {

class SSVMImageLoadJPGToRGB8 : public SSVMImage<SSVMImageLoadJPGToRGB8> {
public:
  Expect<uint32_t> body(Runtime::Instance::MemoryInstance *MemInst,
                        uint32_t ImgBufPtr, uint32_t ImgBufLen,
                        uint32_t TargetImgW, uint32_t TargetImgH,
                        uint32_t DstBufPtr);
};

class SSVMImageLoadJPGToBGR8 : public SSVMImage<SSVMImageLoadJPGToBGR8> {
public:
  Expect<uint32_t> body(Runtime::Instance::MemoryInstance *MemInst,
                        uint32_t ImgBufPtr, uint32_t ImgBufLen,
                        uint32_t TargetImgW, uint32_t TargetImgH,
                        uint32_t DstBufPtr);
};

class SSVMImageLoadJPGToRGB32F : public SSVMImage<SSVMImageLoadJPGToRGB32F> {
public:
  Expect<uint32_t> body(Runtime::Instance::MemoryInstance *MemInst,
                        uint32_t ImgBufPtr, uint32_t ImgBufLen,
                        uint32_t TargetImgW, uint32_t TargetImgH,
                        uint32_t DstBufPtr);
};

class SSVMImageLoadJPGToBGR32F : public SSVMImage<SSVMImageLoadJPGToBGR32F> {
public:
  Expect<uint32_t> body(Runtime::Instance::MemoryInstance *MemInst,
                        uint32_t ImgBufPtr, uint32_t ImgBufLen,
                        uint32_t TargetImgW, uint32_t TargetImgH,
                        uint32_t DstBufPtr);
};

class SSVMImageLoadPNGToRGB8 : public SSVMImage<SSVMImageLoadPNGToRGB8> {
public:
  Expect<uint32_t> body(Runtime::Instance::MemoryInstance *MemInst,
                        uint32_t ImgBufPtr, uint32_t ImgBufLen,
                        uint32_t TargetImgW, uint32_t TargetImgH,
                        uint32_t DstBufPtr);
};

class SSVMImageLoadPNGToBGR8 : public SSVMImage<SSVMImageLoadPNGToBGR8> {
public:
  Expect<uint32_t> body(Runtime::Instance::MemoryInstance *MemInst,
                        uint32_t ImgBufPtr, uint32_t ImgBufLen,
                        uint32_t TargetImgW, uint32_t TargetImgH,
                        uint32_t DstBufPtr);
};

class SSVMImageLoadPNGToRGB32F : public SSVMImage<SSVMImageLoadPNGToRGB32F> {
public:
  Expect<uint32_t> body(Runtime::Instance::MemoryInstance *MemInst,
                        uint32_t ImgBufPtr, uint32_t ImgBufLen,
                        uint32_t TargetImgW, uint32_t TargetImgH,
                        uint32_t DstBufPtr);
};

class SSVMImageLoadPNGToBGR32F : public SSVMImage<SSVMImageLoadPNGToBGR32F> {
public:
  Expect<uint32_t> body(Runtime::Instance::MemoryInstance *MemInst,
                        uint32_t ImgBufPtr, uint32_t ImgBufLen,
                        uint32_t TargetImgW, uint32_t TargetImgH,
                        uint32_t DstBufPtr);
};

} // namespace Host
} // namespace SSVM