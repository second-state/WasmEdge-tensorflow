// SPDX-License-Identifier: Apache-2.0
#include <wasmedge.h>

#include "tensorflowfake_module.h"
#include "tensorflowlite_module.h"
#include "wasmedge-tensorflowlite.h"

#ifdef __cplusplus
extern "C" {
#endif

WasmEdge_ImportObjectContext *WasmEdge_TensorflowLite_ImportObjectCreate() {
  return reinterpret_cast<WasmEdge_ImportObjectContext *>(
      new WasmEdge::Host::WasmEdgeTensorflowLiteModule());
}

WasmEdge_ImportObjectContext *WasmEdge_Tensorflow_ImportObjectCreateDummy() {
  return reinterpret_cast<WasmEdge_ImportObjectContext *>(
      new WasmEdge::Host::WasmEdgeTensorflowFakeModule());
}

#ifdef __cplusplus
} /// extern "C"
#endif
