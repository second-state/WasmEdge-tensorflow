// SPDX-License-Identifier: Apache-2.0
#include "tensorflowlite_module.h"
#include "tensorflowlite_func.h"

#include <memory>

namespace WasmEdge {
namespace Host {

WasmEdgeTensorflowLiteModule::WasmEdgeTensorflowLiteModule()
    : ImportObject("wasmedge_tensorflowlite") {
  addHostFunc("wasmedge_tensorflowlite_create_session",
              std::make_unique<WasmEdgeTensorflowLiteCreateSession>());
  addHostFunc("wasmedge_tensorflowlite_delete_session",
              std::make_unique<WasmEdgeTensorflowLiteDeleteSession>());
  addHostFunc("wasmedge_tensorflowlite_run_session",
              std::make_unique<WasmEdgeTensorflowLiteRunSession>());
  addHostFunc("wasmedge_tensorflowlite_get_output_tensor",
              std::make_unique<WasmEdgeTensorflowLiteGetOutputTensor>());
  addHostFunc("wasmedge_tensorflowlite_get_tensor_len",
              std::make_unique<WasmEdgeTensorflowLiteGetTensorLen>());
  addHostFunc("wasmedge_tensorflowlite_get_tensor_data",
              std::make_unique<WasmEdgeTensorflowLiteGetTensorData>());
  addHostFunc("wasmedge_tensorflowlite_append_input",
              std::make_unique<WasmEdgeTensorflowLiteAppendInput>());
}

} // namespace Host
} // namespace WasmEdge