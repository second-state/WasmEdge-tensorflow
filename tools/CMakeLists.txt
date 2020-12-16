# SPDX-License-Identifier: Apache-2.0
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

add_executable(show-tflite-tensor
  show-tflite-tensor.cpp
)

target_link_libraries(show-tflite-tensor
  PRIVATE
  ${TENSORFLOW_LIB}
)

target_include_directories(show-tflite-tensor
  PUBLIC
  ${TENSORFLOW_INCLUDE}
)