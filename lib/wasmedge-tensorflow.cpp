// SPDX-License-Identifier: Apache-2.0
// SPDX-FileCopyrightText: 2019-2022 Second State INC

#include "wasmedge/wasmedge-tensorflow.h"
#include "tensorflow_module.h"

#ifdef __cplusplus
extern "C" {
#endif

WasmEdge_ModuleInstanceContext *WasmEdge_Tensorflow_ModuleInstanceCreate() {
  return reinterpret_cast<WasmEdge_ModuleInstanceContext *>(
      new WasmEdge::Host::WasmEdgeTensorflowModule());
}

#ifdef __cplusplus
} // extern "C"
#endif
