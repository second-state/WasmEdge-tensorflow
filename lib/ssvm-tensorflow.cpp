// SPDX-License-Identifier: Apache-2.0
#include <ssvm.h>

#include "tensorflowfake_module.h"
#include "tensorflowlite_module.h"

#ifdef __cplusplus
extern "C" {
#endif

SSVM_ImportObjectContext *SSVM_TensorflowLite_ImportObjectCreate() {
  return reinterpret_cast<SSVM_ImportObjectContext *>(
      new SSVM::Host::SSVMTensorflowLiteModule());
}

SSVM_ImportObjectContext *SSVM_Tensorflow_ImportObjectCreateDummy() {
  return reinterpret_cast<SSVM_ImportObjectContext *>(
      new SSVM::Host::SSVMTensorflowFakeModule());
}

#ifdef __cplusplus
} /// extern "C"
#endif
