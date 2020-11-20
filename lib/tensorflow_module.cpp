// SPDX-License-Identifier: Apache-2.0
#include "tensorflow_module.h"
#include "tensorflow_func.h"

#include <memory>

namespace SSVM {
namespace Host {

SSVMTensorflowModule::SSVMTensorflowModule() : ImportObject("ssvm_tensorflow") {
  addHostFunc("ssvm_tensorflow_load_jpg_to_rgb8",
              std::make_unique<SSVMTensorflowLoadJPGToRGB8>(Env));
  addHostFunc("ssvm_tensorflow_load_jpg_to_bgr8",
              std::make_unique<SSVMTensorflowLoadJPGToBGR8>(Env));
  addHostFunc("ssvm_tensorflow_load_jpg_to_rgb32f",
              std::make_unique<SSVMTensorflowLoadJPGToRGB32F>(Env));
  addHostFunc("ssvm_tensorflow_load_jpg_to_bgr32f",
              std::make_unique<SSVMTensorflowLoadJPGToBGR32F>(Env));
  addHostFunc("ssvm_tensorflow_load_png_to_rgb8",
              std::make_unique<SSVMTensorflowLoadPNGToRGB8>(Env));
  addHostFunc("ssvm_tensorflow_load_png_to_bgr8",
              std::make_unique<SSVMTensorflowLoadPNGToBGR8>(Env));
  addHostFunc("ssvm_tensorflow_load_png_to_rgb32f",
              std::make_unique<SSVMTensorflowLoadPNGToRGB32F>(Env));
  addHostFunc("ssvm_tensorflow_load_png_to_bgr32f",
              std::make_unique<SSVMTensorflowLoadPNGToBGR32F>(Env));
  addHostFunc("ssvm_tensorflow_exec_model",
              std::make_unique<SSVMTensorflowExecModel>(Env));
  addHostFunc("ssvm_tensorflow_alloc_tensor",
              std::make_unique<SSVMTensorflowAllocTensor>(Env));
  addHostFunc("ssvm_tensorflow_delete_tensor",
              std::make_unique<SSVMTensorflowDeleteTensor>(Env));
  addHostFunc("ssvm_tensorflow_get_tensor_len",
              std::make_unique<SSVMTensorflowGetTensorLen>(Env));
  addHostFunc("ssvm_tensorflow_get_tensor_data",
              std::make_unique<SSVMTensorflowGetTensorData>(Env));
  addHostFunc("ssvm_tensorflow_append_input",
              std::make_unique<SSVMTensorflowAppendInput>(Env));
  addHostFunc("ssvm_tensorflow_append_output",
              std::make_unique<SSVMTensorflowAppendOutput>(Env));
  addHostFunc("ssvm_tensorflow_clear_input",
              std::make_unique<SSVMTensorflowClearInput>(Env));
  addHostFunc("ssvm_tensorflow_clear_output",
              std::make_unique<SSVMTensorflowClearOutput>(Env));
  addHostFunc("ssvm_tensorflow_get_result_len",
              std::make_unique<SSVMTensorflowGetResultLen>(Env));
  addHostFunc("ssvm_tensorflow_get_result",
              std::make_unique<SSVMTensorflowGetResult>(Env));
}

} // namespace Host
} // namespace SSVM