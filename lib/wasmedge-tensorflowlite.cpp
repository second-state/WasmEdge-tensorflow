// SPDX-License-Identifier: Apache-2.0
// SPDX-FileCopyrightText: 2019-2022 Second State INC

#include "wasmedge/wasmedge-tensorflowlite.h"
#include "tensorflowfake_module.h"
#include "tensorflowlite_module.h"

#ifdef __cplusplus
extern "C" {
#endif

WasmEdge_ModuleInstanceContext *WasmEdge_TensorflowLite_ModuleInstanceCreate() {
  return reinterpret_cast<WasmEdge_ModuleInstanceContext *>(
      new WasmEdge::Host::WasmEdgeTensorflowLiteModule());
}

WasmEdge_ModuleInstanceContext *
WasmEdge_Tensorflow_ModuleInstanceCreateDummy() {
  return reinterpret_cast<WasmEdge_ModuleInstanceContext *>(
      new WasmEdge::Host::WasmEdgeTensorflowFakeModule());
}

#ifdef __cplusplus
} // extern "C"
#endif
