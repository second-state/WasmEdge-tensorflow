# SPDX-License-Identifier: Apache-2.0

configure_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/download_dependencies_all.sh
  ${CMAKE_CURRENT_BINARY_DIR}/download_dependencies_all.sh
  COPYONLY
)
configure_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/download_dependencies_tf.sh
  ${CMAKE_CURRENT_BINARY_DIR}/download_dependencies_tf.sh
  COPYONLY
)
configure_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/download_dependencies_tflite.sh
  ${CMAKE_CURRENT_BINARY_DIR}/download_dependencies_tflite.sh
  COPYONLY
)
message(STATUS "Copying shared library to directory ${CMAKE_CURRENT_BINARY_DIR}/libtensorflowlite_c.so")
configure_file(
  ${ssvmtensorflowdepslite_SOURCE_DIR}/libtensorflowlite_c.so
  ${CMAKE_CURRENT_BINARY_DIR}/libtensorflowlite_c.so
  COPYONLY
)
message(STATUS "Copying shared library to directory ${CMAKE_CURRENT_BINARY_DIR}/libtensorflow.so.2.4.0")
configure_file(
  ${ssvmtensorflowdeps_SOURCE_DIR}/libtensorflow.so.2.4.0
  ${CMAKE_CURRENT_BINARY_DIR}/libtensorflow.so.2.4.0
  COPYONLY
)
message(STATUS "Copying shared library to directory ${CMAKE_CURRENT_BINARY_DIR}/libtensorflow_framework.so.2.4.0")
configure_file(
  ${ssvmtensorflowdeps_SOURCE_DIR}/libtensorflow_framework.so.2.4.0
  ${CMAKE_CURRENT_BINARY_DIR}/libtensorflow_framework.so.2.4.0
  COPYONLY
)
execute_process(
  COMMAND ${CMAKE_COMMAND} -E create_symlink libtensorflow.so.2.4.0 ${CMAKE_CURRENT_BINARY_DIR}/libtensorflow.so.2
  COMMAND ${CMAKE_COMMAND} -E create_symlink libtensorflow.so.2 ${CMAKE_CURRENT_BINARY_DIR}/libtensorflow.so
  COMMAND ${CMAKE_COMMAND} -E create_symlink libtensorflow_framework.so.2.4.0 ${CMAKE_CURRENT_BINARY_DIR}/libtensorflow_framework.so.2
  COMMAND ${CMAKE_COMMAND} -E create_symlink libtensorflow_framework.so.2 ${CMAKE_CURRENT_BINARY_DIR}/libtensorflow_framework.so
)

add_executable(ssvmc-tensorflow
  ssvmc.cpp
)

target_link_libraries(ssvmc-tensorflow
  PRIVATE
  ssvmLoader
  ssvmValidator
  ssvmAOT
  std::filesystem
)

add_executable(ssvm-tensorflow
  ssvmr.cpp
)

target_link_libraries(ssvm-tensorflow
  PRIVATE
  ssvmHostModuleSSVMTensorflow
  ssvmHostModuleSSVMTensorflowLite
  ssvmHostModuleSSVMImage
  ssvmVM
  std::filesystem
  dl
  pthread
)

target_link_options(ssvm-tensorflow
  PUBLIC
  "-static-libstdc++"
)

add_executable(ssvm-tensorflow-lite
  ssvmr-lite.cpp
)

target_link_libraries(ssvm-tensorflow-lite
  PRIVATE
  ssvmHostModuleSSVMTensorflowLite
  ssvmHostModuleSSVMImage
  ssvmVM
  std::filesystem
  dl
  pthread
)

target_link_options(ssvm-tensorflow-lite
  PUBLIC
  "-static-libstdc++"
)

add_executable(show-tflite-tensor
  show-tflite-tensor.cpp
)

target_link_libraries(show-tflite-tensor
  PRIVATE
  ${TENSORFLOW_LITE_LIB}
)

target_include_directories(show-tflite-tensor
  PUBLIC
  ${TENSORFLOW_INCLUDE}
)