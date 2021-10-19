// SPDX-License-Identifier: Apache-2.0
#include "wasmedge/wasmedge-tensorflow.h"
#include "tensorflow_module.h"

#ifdef __cplusplus
extern "C" {
#endif

WasmEdge_ImportObjectContext *WasmEdge_Tensorflow_ImportObjectCreate() {
  return reinterpret_cast<WasmEdge_ImportObjectContext *>(
      new WasmEdge::Host::WasmEdgeTensorflowModule());
}

#ifdef __cplusplus
} /// extern "C"
#endif
