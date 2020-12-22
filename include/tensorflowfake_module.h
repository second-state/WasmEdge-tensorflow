// SPDX-License-Identifier: Apache-2.0
#pragma once

#include "runtime/importobj.h"
#include "tensorflowfake_func.h"

namespace SSVM {
namespace Host {

class SSVMTensorflowFakeModule : public Runtime::ImportObject {
public:
  SSVMTensorflowFakeModule() : ImportObject("ssvm_tensorflow") {
    addHostFunc("ssvm_tensorflow_create_session",
                std::make_unique<SSVMTensorflowFakeCreateSession>());
    addHostFunc("ssvm_tensorflow_delete_session",
                std::make_unique<SSVMTensorflowFakeDeleteSession>());
    addHostFunc("ssvm_tensorflow_run_session",
                std::make_unique<SSVMTensorflowFakeRunSession>());
    addHostFunc("ssvm_tensorflow_get_output_tensor",
                std::make_unique<SSVMTensorflowFakeGetOutputTensor>());
    addHostFunc("ssvm_tensorflow_get_tensor_len",
                std::make_unique<SSVMTensorflowFakeGetTensorLen>());
    addHostFunc("ssvm_tensorflow_get_tensor_data",
                std::make_unique<SSVMTensorflowFakeGetTensorData>());
    addHostFunc("ssvm_tensorflow_append_input",
                std::make_unique<SSVMTensorflowFakeAppendInput>());
    addHostFunc("ssvm_tensorflow_append_output",
                std::make_unique<SSVMTensorflowFakeAppendOutput>());
    addHostFunc("ssvm_tensorflow_clear_input",
                std::make_unique<SSVMTensorflowFakeClearInput>());
    addHostFunc("ssvm_tensorflow_clear_output",
                std::make_unique<SSVMTensorflowFakeClearOutput>());
  }
  ~SSVMTensorflowFakeModule() = default;
};

} // namespace Host
} // namespace SSVM