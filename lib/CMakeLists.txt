# SPDX-License-Identifier: Apache-2.0
# SPDX-FileCopyrightText: 2019-2022 Second State INC

add_library(wasmedgeHostModuleWasmEdgeTensorflow
  tensorflow_module.cpp
  tensorflow_func.cpp
)

target_link_libraries(wasmedgeHostModuleWasmEdgeTensorflow
  PUBLIC
  wasmedgeCommon
  wasmedgeSystem
)

target_include_directories(wasmedgeHostModuleWasmEdgeTensorflow
  PUBLIC
  ${TENSORFLOW_INCLUDE}
  ${WASMEDGE_CORE_PATH}/include
)

add_library(wasmedgeHostModuleWasmEdgeTensorflowLite
  tensorflowlite_module.cpp
  tensorflowlite_func.cpp
)

target_include_directories(wasmedgeHostModuleWasmEdgeTensorflowLite
  PUBLIC
  ${TENSORFLOW_INCLUDE}
  ${WASMEDGE_CORE_PATH}/include
)

target_link_libraries(wasmedgeHostModuleWasmEdgeTensorflowLite
  PUBLIC
  wasmedgeCommon
  wasmedgeSystem
)

if (WASMEDGE_TENSORFLOW_BUILD_SHARED_LIB)
  add_library(wasmedge-tensorflow_c SHARED
    wasmedge-tensorflow.cpp
    tensorflow_module.cpp
    tensorflow_func.cpp
  )

  target_include_directories(wasmedge-tensorflow_c
    PUBLIC
    ${TENSORFLOW_INCLUDE}
    ${WASMEDGE_CORE_PATH}/include
    ${WASMEDGE_CORE_BIN_PATH}/include/api
  )

  target_link_libraries(wasmedge-tensorflow_c
    PRIVATE
    wasmedgeCommon
    wasmedgeSystem
  )

  add_library(wasmedge-tensorflowlite_c SHARED
    wasmedge-tensorflowlite.cpp
    tensorflowlite_module.cpp
    tensorflowlite_func.cpp
  )

  target_include_directories(wasmedge-tensorflowlite_c
    PUBLIC
    ${TENSORFLOW_INCLUDE}
    ${WASMEDGE_CORE_PATH}/include
    ${WASMEDGE_CORE_BIN_PATH}/include/api
  )

  target_link_libraries(wasmedge-tensorflowlite_c
    PRIVATE
    wasmedgeCommon
    wasmedgeSystem
  )
endif()
