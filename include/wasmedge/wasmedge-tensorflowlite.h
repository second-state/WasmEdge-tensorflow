// SPDX-License-Identifier: Apache-2.0
// SPDX-FileCopyrightText: 2019-2022 Second State INC

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

// Need to install the WasmEdge C library first.
#include <wasmedge/wasmedge.h>

#ifdef __cplusplus
extern "C" {
#endif

/// Creation of the WasmEdge_ModuleInstanceContext for the
/// wasmedge_tensorflowlite host functions.
///
/// The caller owns the object and should call `WasmEdge_ModuleInstanceDelete`
/// to destroy it.
///
/// \returns pointer to context, NULL if failed.
WASMEDGE_CAPI_EXPORT extern WasmEdge_ModuleInstanceContext *
WasmEdge_TensorflowLite_ModuleInstanceCreate();

/// Creation of the WasmEdge_ModuleInstanceContext for the wasmedge_tensorflow
/// fake host functions.
///
/// This function will create a dummy wasmedge_tensorflow module instance which
/// the implementation of host functions are all empty. The dummy module
/// instance is used by the runners which only link to the tensorflow-lite
/// shared library and need to accept WASM which want to import
/// wasmedge_tensorflow host functions.
///
/// The caller owns the object and should call `WasmEdge_ModuleInstanceDelete`
/// to destroy it.
///
/// \returns pointer to context, NULL if failed.
WASMEDGE_CAPI_EXPORT extern WasmEdge_ModuleInstanceContext *
WasmEdge_Tensorflow_ModuleInstanceCreateDummy();

#ifdef __cplusplus
} // extern "C"
#endif

#endif // __WASMEDGE_TENSORFLOWLITE_C_API_H__
