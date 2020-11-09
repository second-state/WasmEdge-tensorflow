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
  ssvmVM
  std::filesystem
)
