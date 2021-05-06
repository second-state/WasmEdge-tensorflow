// SPDX-License-Identifier: Apache-2.0
//===-- WasmEdge-tensorflow/wasmedge-tensorflowlite.h - C API -------------===//
//
// Part of the WasmEdge Project.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the function declarations of WasmEdge Tensorflow lite C
/// API.
///
//===----------------------------------------------------------------------===//

#ifndef __WASMEDGE_TENSORFLOWLITE_C_API_H__
#define __WASMEDGE_TENSORFLOWLITE_C_API_H__

#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

/// Need to install the WasmEdge C library first.
#include <wasmedge.h>

#ifdef __cplusplus
extern "C" {
#endif

/// Creation of the WasmEdge_ImportObjectContext for the wasmedge_tensorflowlite
/// host functions.
///
/// The caller owns the object and should call `WasmEdge_ImportObjectDelete` to
/// free it.
///
/// \returns pointer to context, NULL if failed.
WASMEDGE_CAPI_EXPORT extern WasmEdge_ImportObjectContext *
WasmEdge_TensorflowLite_ImportObjectCreate();

/// Creation of the WasmEdge_ImportObjectContext for the wasmedge_tensorflow
/// fake host functions.
///
/// This function will create a dummy wasmedge_tensorflow import object which
/// the implementation of host functions are all empty. The dummy import object
/// is used by the runners which only link to the tensorflow-lite shared library
/// and need to accept WASM which want to import wasmedge_tensorflow host
/// functions.
///
/// The caller owns the object and should call `WasmEdge_ImportObjectDelete` to
/// free it.
///
/// \returns pointer to context, NULL if failed.
WASMEDGE_CAPI_EXPORT extern WasmEdge_ImportObjectContext *
WasmEdge_Tensorflow_ImportObjectCreateDummy();

#ifdef __cplusplus
} /// extern "C"
#endif

#endif /// __WASMEDGE_TENSORFLOWLITE_C_API_H__