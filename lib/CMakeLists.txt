# SPDX-License-Identifier: Apache-2.0

add_library(ssvmHostModuleSSVMTensorflow
  tensorflow_module.cpp
  tensorflow_func.cpp
)

target_link_libraries(ssvmHostModuleSSVMTensorflow
  PRIVATE
  ssvmCommon
  ${TENSORFLOW_LIB}
)

target_include_directories(ssvmHostModuleSSVMTensorflow
  PUBLIC
  ${TENSORFLOW_INCLUDE}
  ${SSVM_CORE_SRC_DIR}/include
  ${SSVM_CORE_SRC_DIR}/thirdparty
)

add_library(ssvmHostModuleSSVMTensorflowLite
  tensorflowlite_module.cpp
  tensorflowlite_func.cpp
)

target_link_libraries(ssvmHostModuleSSVMTensorflowLite
  PRIVATE
  ssvmCommon
  ${TENSORFLOW_LITE_LIB}
)

target_include_directories(ssvmHostModuleSSVMTensorflowLite
  PUBLIC
  ${TENSORFLOW_INCLUDE}
  ${SSVM_CORE_SRC_DIR}/include
  ${SSVM_CORE_SRC_DIR}/thirdparty
)

add_library(ssvmHostModuleSSVMImage
  image_module.cpp
  image_func.cpp
)

target_link_libraries(ssvmHostModuleSSVMImage
  PRIVATE
  ssvmCommon
  ${JPEG_LIB}
  ${PNG_LIB}
)

target_include_directories(ssvmHostModuleSSVMImage
  PUBLIC
  ${JPEG_INCLUDE}
  ${PNG_INCLUDE}
  ${Boost_INCLUDE_DIR}
  ${SSVM_CORE_SRC_DIR}/include
  ${SSVM_CORE_SRC_DIR}/thirdparty
)
