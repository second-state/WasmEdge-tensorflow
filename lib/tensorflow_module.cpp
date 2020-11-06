// SPDX-License-Identifier: Apache-2.0
#include "tensorflow_module.h"
#include "tensorflow_func.h"

#include <memory>

namespace SSVM {
namespace Host {

SSVMTensorflowModule::SSVMTensorflowModule() : ImportObject("ssvm_tensorflow") {
  addHostFunc("ssvm_tensorflow_Mobilenetv2",
              std::make_unique<SSVMTensorflowMobilenetv2>(Env));
  addHostFunc("ssvm_tensorflow_get_result_len",
              std::make_unique<SSVMTensorflowGetResultLen>(Env));
  addHostFunc("ssvm_tensorflow_get_result",
              std::make_unique<SSVMTensorflowGetResult>(Env));
}

} // namespace Host
} // namespace SSVM