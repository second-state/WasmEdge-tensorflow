# SPDX-License-Identifier: Apache-2.0

add_library(ssvmHostModuleSSVMTensorflow
  tensorflow_module.cpp
  tensorflow_func.cpp
)

target_include_directories(ssvmHostModuleSSVMTensorflow
  PUBLIC
  ${TENSORFLOW_INCLUDE}
  ${SSVM_CORE_PATH}/include
  ${SSVM_CORE_PATH}/thirdparty
)

add_library(ssvmHostModuleSSVMTensorflowLite
  tensorflowlite_module.cpp
  tensorflowlite_func.cpp
)

target_include_directories(ssvmHostModuleSSVMTensorflowLite
  PUBLIC
  ${TENSORFLOW_INCLUDE}
  ${SSVM_CORE_PATH}/include
  ${SSVM_CORE_PATH}/thirdparty
)

add_library(ssvm-tensorflow_c SHARED
  ssvm-tensorflow.cpp
  tensorflow_module.cpp
  tensorflow_func.cpp
)

target_include_directories(ssvm-tensorflow_c
  PUBLIC
  ${TENSORFLOW_INCLUDE}
  ${SSVM_CORE_PATH}/include
  ${SSVM_CORE_PATH}/thirdparty
  ${SSVM_CORE_BIN_PATH}/include/api
)

add_library(ssvm-tensorflowlite_c SHARED
  ssvm-tensorflow.cpp
  tensorflowlite_module.cpp
  tensorflowlite_func.cpp
)

target_include_directories(ssvm-tensorflowlite_c
  PUBLIC
  ${TENSORFLOW_INCLUDE}
  ${SSVM_CORE_PATH}/include
  ${SSVM_CORE_PATH}/thirdparty
  ${SSVM_CORE_BIN_PATH}/include/api
)
