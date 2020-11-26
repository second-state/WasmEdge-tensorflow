// SPDX-License-Identifier: Apache-2.0
#include "image_module.h"
#include "image_func.h"

#include <memory>

namespace SSVM {
namespace Host {

SSVMImageModule::SSVMImageModule() : ImportObject("ssvm_image") {
  addHostFunc("ssvm_image_load_jpg_to_rgb8",
              std::make_unique<SSVMImageLoadJPGToRGB8>(Env));
  addHostFunc("ssvm_image_load_jpg_to_bgr8",
              std::make_unique<SSVMImageLoadJPGToBGR8>(Env));
  addHostFunc("ssvm_image_load_jpg_to_rgb32f",
              std::make_unique<SSVMImageLoadJPGToRGB32F>(Env));
  addHostFunc("ssvm_image_load_jpg_to_bgr32f",
              std::make_unique<SSVMImageLoadJPGToBGR32F>(Env));
  addHostFunc("ssvm_image_load_png_to_rgb8",
              std::make_unique<SSVMImageLoadPNGToRGB8>(Env));
  addHostFunc("ssvm_image_load_png_to_bgr8",
              std::make_unique<SSVMImageLoadPNGToBGR8>(Env));
  addHostFunc("ssvm_image_load_png_to_rgb32f",
              std::make_unique<SSVMImageLoadPNGToRGB32F>(Env));
  addHostFunc("ssvm_image_load_png_to_bgr32f",
              std::make_unique<SSVMImageLoadPNGToBGR32F>(Env));
  addHostFunc("ssvm_image_get_result_len",
              std::make_unique<SSVMImageGetResultLen>(Env));
  addHostFunc("ssvm_image_get_result",
              std::make_unique<SSVMImageGetResult>(Env));
}

} // namespace Host
} // namespace SSVM