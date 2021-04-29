// SPDX-License-Identifier: Apache-2.0
//===-- ssvm-tensorflow/ssvm-tensorflow.h - SSVM Tensorflow C API ---------===//
//
// Part of the SSVM Project.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the function declarations of SSVM Tensorflow C API.
///
//===----------------------------------------------------------------------===//

#ifndef __SSVM_TENSORFLOW_C_API_H__
#define __SSVM_TENSORFLOW_C_API_H__

#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

/// Need to install the SSVM C library first.
#include <ssvm.h>

#ifdef __cplusplus
extern "C" {
#endif

/// Creation of the SSVM_ImportObjectContext for the ssvm_tensorflow host
/// functions.
///
/// The caller owns the object and should call `SSVM_ImportObjectDelete` to free
/// it.
///
/// \returns pointer to context, NULL if failed.
SSVM_CAPI_EXPORT extern SSVM_ImportObjectContext *
SSVM_Tensorflow_ImportObjectCreate();

#ifdef __cplusplus
} /// extern "C"
#endif

#endif /// __SSVM_TENSORFLOW_C_API_H__