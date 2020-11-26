// SPDX-License-Identifier: Apache-2.0
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include <boost/gil.hpp>
#include <boost/gil/extension/io/jpeg.hpp>
#include <boost/gil/extension/io/png.hpp>
#include <boost/gil/extension/numeric/resample.hpp>
#include <boost/gil/extension/numeric/sampler.hpp>
#include <boost/gil/io/read_image.hpp>

#include "common/log.h"
#include "common/span.h"
#include "image_func.h"

namespace SSVM {
namespace Host {

namespace {
/// Helper function to read jpeg buffer to gil::image
template <typename Image, typename FormatTag>
bool readBufToImg(const char *Buf, uint32_t Len, Image &Img,
                  FormatTag const &FTag) {
  std::stringstream ImgStream;
  ImgStream.write(Buf, Len);
  try {
    boost::gil::read_image(ImgStream, Img, FTag);
  } catch (std::exception const &e) {
    LOG(ERROR) << e.what();
    return false;
  }
  return true;
}

/// Helper function to resize image. 8-bit depth only.
template <typename Image>
std::vector<uint8_t> resizeImg(const Image &Img, uint32_t W, uint32_t H) {
  uint32_t C = boost::gil::num_channels<typename Image::view_t>::value;
  std::vector<uint8_t> ImgData(C * W * H);
  typename Image::view_t ImgView = boost::gil::interleaved_view(
      W, H, (typename Image::value_type *)(&ImgData[0]),
      W * C * sizeof(uint8_t));
  boost::gil::resize_view(boost::gil::const_view(Img), ImgView,
                          boost::gil::bilinear_sampler());
  return ImgData;
}

/// Helper function to normalize and resize image
std::vector<float> normalizeImg(Span<const uint8_t> V) {
  std::vector<float> Flat(V.size());
  std::transform(V.begin(), V.end(), Flat.begin(),
                 [](uint8_t P) -> float { return P / 255.0; });
  return Flat;
}
} // namespace

Expect<uint32_t>
SSVMImageLoadJPGToRGB8::body(Runtime::Instance::MemoryInstance *MemInst,
                             uint32_t ImgBufPtr, uint32_t ImgBufLen,
                             uint32_t TargetImgW, uint32_t TargetImgH) {
  /// Check memory instance from module.
  if (MemInst == nullptr) {
    return Unexpect(ErrCode::ExecutionFailed);
  }

  boost::gil::rgb8_image_t Img;
  if (!readBufToImg(MemInst->getPointer<char *>(ImgBufPtr), ImgBufLen, Img,
                    boost::gil::jpeg_tag())) {
    return 1;
  }
  Env.Res = resizeImg(Img, TargetImgW, TargetImgH);
  return 0;
}

Expect<uint32_t>
SSVMImageLoadJPGToBGR8::body(Runtime::Instance::MemoryInstance *MemInst,
                             uint32_t ImgBufPtr, uint32_t ImgBufLen,
                             uint32_t TargetImgW, uint32_t TargetImgH) {
  /// Check memory instance from module.
  if (MemInst == nullptr) {
    return Unexpect(ErrCode::ExecutionFailed);
  }

  boost::gil::bgr8_image_t Img;
  if (!readBufToImg(MemInst->getPointer<char *>(ImgBufPtr), ImgBufLen, Img,
                    boost::gil::jpeg_tag())) {
    return 1;
  }
  Env.Res = resizeImg(Img, TargetImgW, TargetImgH);
  return 0;
}

Expect<uint32_t>
SSVMImageLoadJPGToRGB32F::body(Runtime::Instance::MemoryInstance *MemInst,
                               uint32_t ImgBufPtr, uint32_t ImgBufLen,
                               uint32_t TargetImgW, uint32_t TargetImgH) {
  /// Check memory instance from module.
  if (MemInst == nullptr) {
    return Unexpect(ErrCode::ExecutionFailed);
  }

  boost::gil::rgb8_image_t Img;
  if (!readBufToImg(MemInst->getPointer<char *>(ImgBufPtr), ImgBufLen, Img,
                    boost::gil::jpeg_tag())) {
    return 1;
  }
  auto Resized = resizeImg(Img, TargetImgW, TargetImgH);
  auto Flat = normalizeImg(Resized);
  uint8_t *Start = reinterpret_cast<uint8_t *>(&Flat[0]);
  Env.Res = std::vector<uint8_t>(Start, Start + sizeof(float) * Flat.size());
  return 0;
}

Expect<uint32_t>
SSVMImageLoadJPGToBGR32F::body(Runtime::Instance::MemoryInstance *MemInst,
                               uint32_t ImgBufPtr, uint32_t ImgBufLen,
                               uint32_t TargetImgW, uint32_t TargetImgH) {
  /// Check memory instance from module.
  if (MemInst == nullptr) {
    return Unexpect(ErrCode::ExecutionFailed);
  }

  boost::gil::bgr8_image_t Img;
  if (!readBufToImg(MemInst->getPointer<char *>(ImgBufPtr), ImgBufLen, Img,
                    boost::gil::jpeg_tag())) {
    return 1;
  }
  auto Resized = resizeImg(Img, TargetImgW, TargetImgH);
  auto Flat = normalizeImg(Resized);
  uint8_t *Start = reinterpret_cast<uint8_t *>(&Flat[0]);
  Env.Res = std::vector<uint8_t>(Start, Start + sizeof(float) * Flat.size());
  return 0;
}

Expect<uint32_t>
SSVMImageLoadPNGToRGB8::body(Runtime::Instance::MemoryInstance *MemInst,
                             uint32_t ImgBufPtr, uint32_t ImgBufLen,
                             uint32_t TargetImgW, uint32_t TargetImgH) {
  /// Check memory instance from module.
  if (MemInst == nullptr) {
    return Unexpect(ErrCode::ExecutionFailed);
  }

  boost::gil::rgb8_image_t Img;
  if (!readBufToImg(MemInst->getPointer<char *>(ImgBufPtr), ImgBufLen, Img,
                    boost::gil::png_tag())) {
    return 1;
  }
  Env.Res = resizeImg(Img, TargetImgW, TargetImgH);
  return 0;
}

Expect<uint32_t>
SSVMImageLoadPNGToBGR8::body(Runtime::Instance::MemoryInstance *MemInst,
                             uint32_t ImgBufPtr, uint32_t ImgBufLen,
                             uint32_t TargetImgW, uint32_t TargetImgH) {
  /// Check memory instance from module.
  if (MemInst == nullptr) {
    return Unexpect(ErrCode::ExecutionFailed);
  }

  boost::gil::bgr8_image_t Img;
  if (!readBufToImg(MemInst->getPointer<char *>(ImgBufPtr), ImgBufLen, Img,
                    boost::gil::png_tag())) {
    return 1;
  }
  Env.Res = resizeImg(Img, TargetImgW, TargetImgH);
  return 0;
}

Expect<uint32_t>
SSVMImageLoadPNGToRGB32F::body(Runtime::Instance::MemoryInstance *MemInst,
                               uint32_t ImgBufPtr, uint32_t ImgBufLen,
                               uint32_t TargetImgW, uint32_t TargetImgH) {
  /// Check memory instance from module.
  if (MemInst == nullptr) {
    return Unexpect(ErrCode::ExecutionFailed);
  }

  boost::gil::rgb8_image_t Img;
  if (!readBufToImg(MemInst->getPointer<char *>(ImgBufPtr), ImgBufLen, Img,
                    boost::gil::png_tag())) {
    return 1;
  }
  auto Resized = resizeImg(Img, TargetImgW, TargetImgH);
  auto Flat = normalizeImg(Resized);
  uint8_t *Start = reinterpret_cast<uint8_t *>(&Flat[0]);
  Env.Res = std::vector<uint8_t>(Start, Start + sizeof(float) * Flat.size());
  return 0;
}

Expect<uint32_t>
SSVMImageLoadPNGToBGR32F::body(Runtime::Instance::MemoryInstance *MemInst,
                               uint32_t ImgBufPtr, uint32_t ImgBufLen,
                               uint32_t TargetImgW, uint32_t TargetImgH) {
  /// Check memory instance from module.
  if (MemInst == nullptr) {
    return Unexpect(ErrCode::ExecutionFailed);
  }

  boost::gil::bgr8_image_t Img;
  if (!readBufToImg(MemInst->getPointer<char *>(ImgBufPtr), ImgBufLen, Img,
                    boost::gil::png_tag())) {
    return 1;
  }
  auto Resized = resizeImg(Img, TargetImgW, TargetImgH);
  auto Flat = normalizeImg(Resized);
  uint8_t *Start = reinterpret_cast<uint8_t *>(&Flat[0]);
  Env.Res = std::vector<uint8_t>(Start, Start + sizeof(float) * Flat.size());
  return 0;
}

Expect<uint32_t>
SSVMImageGetResultLen::body(Runtime::Instance::MemoryInstance *MemInst) {
  return Env.Res.size();
}

Expect<void>
SSVMImageGetResult::body(Runtime::Instance::MemoryInstance *MemInst,
                         uint32_t BufPtr) {
  /// Check memory instance from module.
  if (MemInst == nullptr) {
    return Unexpect(ErrCode::ExecutionFailed);
  }

  uint8_t *Buf = MemInst->getPointer<uint8_t *>(BufPtr);
  if (Env.Res.size() > 0) {
    std::copy_n(Env.Res.begin(), Env.Res.size(), Buf);
  }
  return {};
}

} // namespace Host
} // namespace SSVM
