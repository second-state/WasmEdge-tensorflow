# SPDX-License-Identifier: Apache-2.0

add_library(ssvmHostModuleSSVMTensorflow
  tensorflow_module.cpp
  tensorflow_func.cpp
)

target_link_libraries(ssvmHostModuleSSVMTensorflow
  PRIVATE
  ssvmCommon
  ${TensorFlow_LIBRARIES}
)

target_include_directories(ssvmHostModuleSSVMTensorflow
  PUBLIC
  ${TensorFlow_INCLUDE_DIR}
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
  ${TENSORFLOW_LITE_INCLUDE}
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
  ${JPEG_LIBRARIES}
  ${PNG_LIBRARIES}
)

target_include_directories(ssvmHostModuleSSVMImage
  PUBLIC
  ${Boost_INCLUDE_DIR}
  ${SSVM_CORE_SRC_DIR}/include
  ${SSVM_CORE_SRC_DIR}/thirdparty
)
