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

add_executable(ssvm-tensorflow-lite
  ssvmr-lite.cpp
)

target_link_libraries(ssvm-tensorflow-lite
  PRIVATE
  ssvmHostModuleSSVMTensorflowLite
  ssvmHostModuleSSVMImage
  ssvmVM
  std::filesystem
)

target_link_options(ssvm-tensorflow-lite BEFORE
  PUBLIC
  "-Wl,-Bstatic"
  "-ldl"
  "-pthread"
  "-static-libgcc"
)
