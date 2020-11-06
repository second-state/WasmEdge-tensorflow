# SPDX-License-Identifier: Apache-2.0

add_library(ssvmHostModuleSSVMTensorflow
  tensorflow_module.cpp
  tensorflow_func.cpp
)

target_link_libraries(ssvmHostModuleSSVMTensorflow
  PRIVATE
  ssvmCommon
  ${JPEG_LIBRARIES}
  ${TensorFlow_LIBRARIES}
)

target_include_directories(ssvmHostModuleSSVMTensorflow
  PUBLIC
  ${TensorFlow_INCLUDE_DIR}
  ${Boost_INCLUDE_DIR}
  ${SSVM_CORE_SRC_DIR}/include
  ${SSVM_CORE_SRC_DIR}/thirdparty
)
