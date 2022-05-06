// SPDX-License-Identifier: Apache-2.0
// SPDX-FileCopyrightText: 2019-2022 Second State INC

#include "tensorflow_module.h"
#include "tensorflow_func.h"

#include <memory>

namespace WasmEdge {
namespace Host {

WasmEdgeTensorflowModule::WasmEdgeTensorflowModule()
    : Runtime::Instance::ModuleInstance("wasmedge_tensorflow") {
  addHostFunc("wasmedge_tensorflow_create_session",
              std::make_unique<WasmEdgeTensorflowCreateSession>());
  addHostFunc("wasmedge_tensorflow_delete_session",
              std::make_unique<WasmEdgeTensorflowDeleteSession>());
  addHostFunc("wasmedge_tensorflow_run_session",
              std::make_unique<WasmEdgeTensorflowRunSession>());
  addHostFunc("wasmedge_tensorflow_get_output_tensor",
              std::make_unique<WasmEdgeTensorflowGetOutputTensor>());
  addHostFunc("wasmedge_tensorflow_get_tensor_len",
              std::make_unique<WasmEdgeTensorflowGetTensorLen>());
  addHostFunc("wasmedge_tensorflow_get_tensor_data",
              std::make_unique<WasmEdgeTensorflowGetTensorData>());
  addHostFunc("wasmedge_tensorflow_append_input",
              std::make_unique<WasmEdgeTensorflowAppendInput>());
  addHostFunc("wasmedge_tensorflow_append_output",
              std::make_unique<WasmEdgeTensorflowAppendOutput>());
  addHostFunc("wasmedge_tensorflow_clear_input",
              std::make_unique<WasmEdgeTensorflowClearInput>());
  addHostFunc("wasmedge_tensorflow_clear_output",
              std::make_unique<WasmEdgeTensorflowClearOutput>());
}

} // namespace Host
} // namespace WasmEdge
