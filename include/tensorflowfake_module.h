// SPDX-License-Identifier: Apache-2.0
// SPDX-FileCopyrightText: 2019-2022 Second State INC

#pragma once

#include "runtime/importobj.h"
#include "tensorflowfake_func.h"

namespace WasmEdge {
namespace Host {

class WasmEdgeTensorflowFakeModule : public Runtime::ImportObject {
public:
  WasmEdgeTensorflowFakeModule() : ImportObject("wasmedge_tensorflow") {
    addHostFunc("wasmedge_tensorflow_create_session",
                std::make_unique<WasmEdgeTensorflowFakeCreateSession>());
    addHostFunc("wasmedge_tensorflow_delete_session",
                std::make_unique<WasmEdgeTensorflowFakeDeleteSession>());
    addHostFunc("wasmedge_tensorflow_run_session",
                std::make_unique<WasmEdgeTensorflowFakeRunSession>());
    addHostFunc("wasmedge_tensorflow_get_output_tensor",
                std::make_unique<WasmEdgeTensorflowFakeGetOutputTensor>());
    addHostFunc("wasmedge_tensorflow_get_tensor_len",
                std::make_unique<WasmEdgeTensorflowFakeGetTensorLen>());
    addHostFunc("wasmedge_tensorflow_get_tensor_data",
                std::make_unique<WasmEdgeTensorflowFakeGetTensorData>());
    addHostFunc("wasmedge_tensorflow_append_input",
                std::make_unique<WasmEdgeTensorflowFakeAppendInput>());
    addHostFunc("wasmedge_tensorflow_append_output",
                std::make_unique<WasmEdgeTensorflowFakeAppendOutput>());
    addHostFunc("wasmedge_tensorflow_clear_input",
                std::make_unique<WasmEdgeTensorflowFakeClearInput>());
    addHostFunc("wasmedge_tensorflow_clear_output",
                std::make_unique<WasmEdgeTensorflowFakeClearOutput>());
  }
  ~WasmEdgeTensorflowFakeModule() = default;
};

} // namespace Host
} // namespace WasmEdge
