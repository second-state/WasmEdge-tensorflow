// SPDX-License-Identifier: Apache-2.0
//===-- ssvm-tensorflow/ssvm-tensorflowlite.h - SSVM Tensorflow lite C API ===//
//
// Part of the SSVM Project.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the function declarations of SSVM Tensorflow lite C API.
///
//===----------------------------------------------------------------------===//

#ifndef __SSVM_TENSORFLOWLITE_C_API_H__
#define __SSVM_TENSORFLOWLITE_C_API_H__

#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

/// Need to install the SSVM C library first.
#include <ssvm.h>

#ifdef __cplusplus
extern "C" {
#endif

/// Creation of the SSVM_ImportObjectContext for the ssvm_tensorflowlite host
/// functions.
///
/// The caller owns the object and should call `SSVM_ImportObjectDelete` to free
/// it.
///
/// \returns pointer to context, NULL if failed.
SSVM_CAPI_EXPORT extern SSVM_ImportObjectContext *
SSVM_TensorflowLite_ImportObjectCreate();

/// Creation of the SSVM_ImportObjectContext for the ssvm_tensorflow fake host
/// functions.
///
/// This function will create a dummy ssvm_tensorflow import object which the
/// implementation of host functions are all empty. The dummy import object is
/// used by the runners which only link to the tensorflow-lite shared library
/// and need to accept WASM which want to import ssvm_tensorflow host functions.
///
/// The caller owns the object and should call `SSVM_ImportObjectDelete` to free
/// it.
///
/// \returns pointer to context, NULL if failed.
SSVM_CAPI_EXPORT extern SSVM_ImportObjectContext *
SSVM_Tensorflow_ImportObjectCreateDummy();

#ifdef __cplusplus
} /// extern "C"
#endif

#endif /// __SSVM_TENSORFLOWLITE_C_API_H__