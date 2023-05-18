# SPDX-License-Identifier: Apache-2.0
# SPDX-FileCopyrightText: 2019-2022 Second State INC

# Determine the TensorFlow is need to build.
if(APPLE OR (UNIX AND NOT ANDROID))
  set(WASMEDGE_TENSORFLOW_BUILD_TF ON)
endif()

if(WASMEDGE_TENSORFLOW_BUILD_TF)
  # Build WasmEdge-Tensoflow.
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
endif()

# Build WasmEdge-Tensoflow-Lite.
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

# Linking libwasmedge-tensorflowlite_c.so for Android needs the libtensorflowlite_c.so.
if(ANDROID)
  if(NOT WASMEDGE_TENSORFLOW_DEPS_TFLITE_LIB)
    FetchContent_Declare(
      wasmedgetensorflowdepslite
      URL      "https://github.com/second-state/WasmEdge-tensorflow-deps/releases/download/${WASMEDGE_DEPS_VERSION}/WasmEdge-tensorflow-deps-TFLite-${WASMEDGE_DEPS_VERSION}-android_aarch64.tar.gz"
      URL_HASH "SHA256=2d7dcd7381479d9ffc0968ea66e24a5207b404c7f2ccbdddec6f2a4d6f9813f2"
    )
    FetchContent_GetProperties(wasmedgetensorflowdepslite)
    if (NOT wasmedgetensorflowdepslite_POPULATED)
      FetchContent_Populate(wasmedgetensorflowdepslite)
    endif()
    set(WASMEDGE_TENSORFLOW_DEPS_TFLITE_LIB
      "${wasmedgetensorflowdepslite_SOURCE_DIR}/libtensorflowlite_c.so"
    )
  endif()
endif()

# Linking libwasmedge-tensorflow_c.dylib for MacOS needs the libtensorflow_cc.2.6.0.dylib and libtensorflow_framework.2.6.0.dylib.
# Linking libwasmedge-tensorflowlite_c.dylib for MacOS needs the libtensorflowlite_c.dylib and libtensorflowlite_flex.dylib.
if(APPLE)
  if(NOT WASMEDGE_TENSORFLOW_DEPS_TFLITE_LIB)
    if(WASMEDGE_TENSORFLOW_SYSTEM_NAME STREQUAL "darwin_x86_64")
      set(WASMEDGE_TENSORFLOW_DEPS_TFLITE_HASH "04b58f4b97220633a8e299a63aba73d9a1f228904081e7d5f18e78d1e38d5f00")
    elseif(WASMEDGE_TENSORFLOW_SYSTEM_NAME STREQUAL "darwin_arm64")
      set(WASMEDGE_TENSORFLOW_DEPS_TFLITE_HASH "cb4562a80ac2067bdabe2464b80e129b9d8ddc6d97ad1a2d7215e06a1e1e8cda")
    endif()

    FetchContent_Declare(
      wasmedgetensorflowdepslite
      URL      "https://github.com/second-state/WasmEdge-tensorflow-deps/releases/download/${WASMEDGE_DEPS_VERSION}/WasmEdge-tensorflow-deps-TFLite-${WASMEDGE_DEPS_VERSION}-${WASMEDGE_TENSORFLOW_SYSTEM_NAME}.tar.gz"
      URL_HASH "SHA256=${WASMEDGE_TENSORFLOW_DEPS_TFLITE_HASH}"
    )
    FetchContent_GetProperties(wasmedgetensorflowdepslite)
    if (NOT wasmedgetensorflowdepslite_POPULATED)
      FetchContent_Populate(wasmedgetensorflowdepslite)
    endif()
    set(WASMEDGE_TENSORFLOW_DEPS_TFLITE_LIB
      "${wasmedgetensorflowdepslite_SOURCE_DIR}/libtensorflowlite_c.dylib"
      "${wasmedgetensorflowdepslite_SOURCE_DIR}/libtensorflowlite_flex.dylib"
    )
  endif()

  if(WASMEDGE_TENSORFLOW_BUILD_TF AND NOT WASMEDGE_TENSORFLOW_DEPS_TF_LIB)
    if(WASMEDGE_TENSORFLOW_SYSTEM_NAME STREQUAL "darwin_x86_64")
      set(WASMEDGE_TENSORFLOW_DEPS_TF_HASH "60da72a093cf65d733ca2cb9f331356a1637acfe1645050809bd0cf056b1520f")
    elseif(WASMEDGE_TENSORFLOW_SYSTEM_NAME STREQUAL "darwin_arm64")
      set(WASMEDGE_TENSORFLOW_DEPS_TF_HASH "2ede6d96c7563eb826331469d7d0a1f51c9b1ca311f4398d841f679a5b96705a")
    endif()

    FetchContent_Declare(
      wasmedgetensorflowdeps
      URL      "https://github.com/second-state/WasmEdge-tensorflow-deps/releases/download/${WASMEDGE_DEPS_VERSION}/WasmEdge-tensorflow-deps-TF-${WASMEDGE_DEPS_VERSION}-${WASMEDGE_TENSORFLOW_SYSTEM_NAME}.tar.gz"
      URL_HASH "SHA256=${WASMEDGE_TENSORFLOW_DEPS_TF_HASH}"
    )
    FetchContent_GetProperties(wasmedgetensorflowdeps)
    if(NOT wasmedgetensorflowdeps_POPULATED)
      FetchContent_Populate(wasmedgetensorflowdeps)
      execute_process(
        COMMAND ${CMAKE_COMMAND} -E create_symlink libtensorflow_cc.2.12.0.dylib ${wasmedgetensorflowdeps_SOURCE_DIR}/libtensorflow_cc.2.dylib
        COMMAND ${CMAKE_COMMAND} -E create_symlink libtensorflow_cc.2.dylib ${wasmedgetensorflowdeps_SOURCE_DIR}/libtensorflow_cc.dylib
        COMMAND ${CMAKE_COMMAND} -E create_symlink libtensorflow_framework.2.12.0.dylib ${wasmedgetensorflowdeps_SOURCE_DIR}/libtensorflow_framework.2.dylib
        COMMAND ${CMAKE_COMMAND} -E create_symlink libtensorflow_framework.2.dylib ${wasmedgetensorflowdeps_SOURCE_DIR}/libtensorflow_framework.dylib
      )
    endif()
    set(WASMEDGE_TENSORFLOW_DEPS_TF_LIB
      "${wasmedgetensorflowdeps_SOURCE_DIR}/libtensorflow_cc.2.12.0.dylib"
      "${wasmedgetensorflowdeps_SOURCE_DIR}/libtensorflow_framework.2.12.0.dylib"
    )
  endif()
endif()

# Build WasmEdge-TensorFlow and WasmEdge-TensorFlow-Lite C-API.
if(WASMEDGE_TENSORFLOW_BUILD_SHARED_LIB)
  if(WASMEDGE_TENSORFLOW_BUILD_TF)
    # Build WasmEdge-TensorFlow C-API.
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

    if(APPLE)
      target_link_libraries(wasmedge-tensorflow_c
        PRIVATE
        ${WASMEDGE_TENSORFLOW_DEPS_TF_LIB}
      )
    endif()
  endif()

  # Build WasmEdge-TensorFlow-Lite C-API.
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

  if(ANDROID OR APPLE)
    target_link_libraries(wasmedge-tensorflowlite_c
      PRIVATE
      ${WASMEDGE_TENSORFLOW_DEPS_TFLITE_LIB}
    )
  endif()
endif()
