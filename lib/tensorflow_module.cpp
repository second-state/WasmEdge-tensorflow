// SPDX-License-Identifier: Apache-2.0
#include "tensorflow_module.h"
#include "tensorflow_func.h"

#include <memory>

namespace SSVM {
namespace Host {

SSVMTensorflowModule::SSVMTensorflowModule() : ImportObject("ssvm_tensorflow") {
  addHostFunc("ssvm_tensorflow_run_vision",
              std::make_unique<SSVMTensorflowRunVision>(Env));
  addHostFunc("ssvm_tensorflow_append_input",
              std::make_unique<SSVMTensorflowAppendInput>(Env));
  addHostFunc("ssvm_tensorflow_append_output",
              std::make_unique<SSVMTensorflowAppendOutput>(Env));
  addHostFunc("ssvm_tensorflow_get_result_len",
              std::make_unique<SSVMTensorflowGetResultLen>(Env));
  addHostFunc("ssvm_tensorflow_get_result",
              std::make_unique<SSVMTensorflowGetResult>(Env));
}

} // namespace Host
} // namespace SSVM