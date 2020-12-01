// SPDX-License-Identifier: Apache-2.0
#include "tensorflow_module.h"
#include "tensorflow_func.h"

#include <memory>

namespace SSVM {
namespace Host {

SSVMTensorflowModule::SSVMTensorflowModule() : ImportObject("ssvm_tensorflow") {
  addHostFunc("ssvm_tensorflow_create_session",
              std::make_unique<SSVMTensorflowCreateSession>());
  addHostFunc("ssvm_tensorflow_delete_session",
              std::make_unique<SSVMTensorflowDeleteSession>());
  addHostFunc("ssvm_tensorflow_run_session",
              std::make_unique<SSVMTensorflowRunSession>());
  addHostFunc("ssvm_tensorflow_get_output_tensor",
              std::make_unique<SSVMTensorflowGetOutputTensor>());
  addHostFunc("ssvm_tensorflow_get_tensor_len",
              std::make_unique<SSVMTensorflowGetTensorLen>());
  addHostFunc("ssvm_tensorflow_get_tensor_data",
              std::make_unique<SSVMTensorflowGetTensorData>());
  addHostFunc("ssvm_tensorflow_append_input",
              std::make_unique<SSVMTensorflowAppendInput>());
  addHostFunc("ssvm_tensorflow_append_output",
              std::make_unique<SSVMTensorflowAppendOutput>());
  addHostFunc("ssvm_tensorflow_clear_input",
              std::make_unique<SSVMTensorflowClearInput>());
  addHostFunc("ssvm_tensorflow_clear_output",
              std::make_unique<SSVMTensorflowClearOutput>());
}

} // namespace Host
} // namespace SSVM