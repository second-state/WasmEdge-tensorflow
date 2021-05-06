# SPDX-License-Identifier: Apache-2.0

add_library(wasmedgeHostModuleWasmEdgeTensorflow
  tensorflow_module.cpp
  tensorflow_func.cpp
)

target_include_directories(wasmedgeHostModuleWasmEdgeTensorflow
  PUBLIC
  ${TENSORFLOW_INCLUDE}
  ${WASMEDGE_CORE_PATH}/include
  ${WASMEDGE_CORE_PATH}/thirdparty
)

add_library(wasmedgeHostModuleWasmEdgeTensorflowLite
  tensorflowlite_module.cpp
  tensorflowlite_func.cpp
)

target_include_directories(wasmedgeHostModuleWasmEdgeTensorflowLite
  PUBLIC
  ${TENSORFLOW_INCLUDE}
  ${WASMEDGE_CORE_PATH}/include
  ${WASMEDGE_CORE_PATH}/thirdparty
)

add_library(wasmedge-tensorflow_c SHARED
  wasmedge-tensorflow.cpp
  tensorflow_module.cpp
  tensorflow_func.cpp
)

target_include_directories(wasmedge-tensorflow_c
  PUBLIC
  ${TENSORFLOW_INCLUDE}
  ${WASMEDGE_CORE_PATH}/include
  ${WASMEDGE_CORE_PATH}/thirdparty
  ${WASMEDGE_CORE_BIN_PATH}/include/api
)

add_library(wasmedge-tensorflowlite_c SHARED
  wasmedge-tensorflow.cpp
  tensorflowlite_module.cpp
  tensorflowlite_func.cpp
)

target_include_directories(wasmedge-tensorflowlite_c
  PUBLIC
  ${TENSORFLOW_INCLUDE}
  ${WASMEDGE_CORE_PATH}/include
  ${WASMEDGE_CORE_PATH}/thirdparty
  ${WASMEDGE_CORE_BIN_PATH}/include/api
)
