// SPDX-License-Identifier: Apache-2.0
#include "tensorflowlite_module.h"
#include "tensorflowlite_func.h"

#include <memory>

namespace SSVM {
namespace Host {

SSVMTensorflowLiteModule::SSVMTensorflowLiteModule()
    : ImportObject("ssvm_tensorflowlite") {
  addHostFunc("ssvm_tensorflowlite_create_session",
              std::make_unique<SSVMTensorflowLiteCreateSession>());
  addHostFunc("ssvm_tensorflowlite_delete_session",
              std::make_unique<SSVMTensorflowLiteDeleteSession>());
  addHostFunc("ssvm_tensorflowlite_run_session",
              std::make_unique<SSVMTensorflowLiteRunSession>());
  addHostFunc("ssvm_tensorflowlite_get_output_tensor",
              std::make_unique<SSVMTensorflowLiteGetOutputTensor>());
  addHostFunc("ssvm_tensorflowlite_get_tensor_len",
              std::make_unique<SSVMTensorflowLiteGetTensorLen>());
  addHostFunc("ssvm_tensorflowlite_get_tensor_data",
              std::make_unique<SSVMTensorflowLiteGetTensorData>());
  addHostFunc("ssvm_tensorflowlite_append_input",
              std::make_unique<SSVMTensorflowLiteAppendInput>());
}

} // namespace Host
} // namespace SSVM