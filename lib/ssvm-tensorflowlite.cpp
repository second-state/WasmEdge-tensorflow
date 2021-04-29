// SPDX-License-Identifier: Apache-2.0
#include <ssvm.h>

#include "tensorflow_module.h"

#ifdef __cplusplus
extern "C" {
#endif

SSVM_ImportObjectContext *SSVM_Tensorflow_ImportObjectCreate() {
  return reinterpret_cast<SSVM_ImportObjectContext *>(
      new SSVM::Host::SSVMTensorflowModule());
}

#ifdef __cplusplus
} /// extern "C"
#endif
