# SPDX-License-Identifier: Apache-2.0
# SPDX-FileCopyrightText: 2019-2022 Second State INC

# Determine the TensorFlow is need to build.
if(CMAKE_SYSTEM_PROCESSOR STREQUAL "x86_64" OR CMAKE_SYSTEM_PROCESSOR STREQUAL "AMD64")
  if((UNIX AND NOT ANDROID) OR APPLE)
    set(WASMEDGE_TENSORFLOW_BUILD_TF ON)
  endif()
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

# FIXME: This is a workaround solution.
# Linking libwasmedge-tensorflowlite_c.so for Android needs the libtensorflowlite_c.so.
if(ANDROID)
  if(NOT WASMEDGE_TENSORFLOW_DEPS_TFLITE_LIB)
    FetchContent_Declare(
      wasmedgetensorflowdepslite
      URL      "https://github.com/second-state/WasmEdge-tensorflow-deps/releases/download/${WASMEDGE_DEPS_VERSION}/WasmEdge-tensorflow-deps-TFLite-${WASMEDGE_DEPS_VERSION}-android_aarch64.tar.gz"
      URL_HASH "SHA256=a25dafad049cbc998c1f9682c57aec22b2fe5799eeffdd4ed19793a734cde8a4"
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

# FIXME: This is a workaround solution.
# Linking libwasmedge-tensorflow_c.dylib for MacOS needs the libtensorflow_cc.2.6.0.dylib and libtensorflow_framework.2.6.0.dylib.
# Linking libwasmedge-tensorflowlite_c.dylib for MacOS needs the libtensorflow_c.dylib.
if(APPLE)
  # FIXME: Support M1 in the future.
  if(NOT WASMEDGE_TENSORFLOW_DEPS_TFLITE_LIB)
    FetchContent_Declare(
      wasmedgetensorflowdepslite
      URL      "https://github.com/second-state/WasmEdge-tensorflow-deps/releases/download/${WASMEDGE_DEPS_VERSION}/WasmEdge-tensorflow-deps-TFLite-${WASMEDGE_DEPS_VERSION}-darwin_x86_64.tar.gz"
      URL_HASH "SHA256=2593772df440a768e79d87e74a860378f46fb0b7d1e7805879ab2ec26a093b57"
    )
    FetchContent_GetProperties(wasmedgetensorflowdepslite)
    if (NOT wasmedgetensorflowdepslite_POPULATED)
      FetchContent_Populate(wasmedgetensorflowdepslite)
    endif()
    set(WASMEDGE_TENSORFLOW_DEPS_TFLITE_LIB
      "${wasmedgetensorflowdepslite_SOURCE_DIR}/libtensorflowlite_c.dylib"
    )
  endif()
  if(WASMEDGE_TENSORFLOW_BUILD_TF AND NOT WASMEDGE_TENSORFLOW_DEPS_TF_LIB)
    FetchContent_Declare(
      wasmedgetensorflowdeps
      URL      "https://github.com/second-state/WasmEdge-tensorflow-deps/releases/download/${WASMEDGE_DEPS_VERSION}/WasmEdge-tensorflow-deps-TF-${WASMEDGE_DEPS_VERSION}-darwin_x86_64.tar.gz"
      URL_HASH "SHA256=c1906b81b5db7f6f4fefce3c825a240a92f0d897dee41e2e1b294c9173132f2d"
    )
    FetchContent_GetProperties(wasmedgetensorflowdeps)
    if(NOT wasmedgetensorflowdeps_POPULATED)
      FetchContent_Populate(wasmedgetensorflowdeps)
      execute_process(
        COMMAND ${CMAKE_COMMAND} -E create_symlink libtensorflow_cc.2.6.0.dylib ${wasmedgetensorflowdeps_SOURCE_DIR}/libtensorflow_cc.2.dylib
        COMMAND ${CMAKE_COMMAND} -E create_symlink libtensorflow_cc.2.dylib ${wasmedgetensorflowdeps_SOURCE_DIR}/libtensorflow_cc.dylib
        COMMAND ${CMAKE_COMMAND} -E create_symlink libtensorflow_framework.2.6.0.dylib ${wasmedgetensorflowdeps_SOURCE_DIR}/libtensorflow_framework.2.dylib
        COMMAND ${CMAKE_COMMAND} -E create_symlink libtensorflow_framework.2.dylib ${wasmedgetensorflowdeps_SOURCE_DIR}/libtensorflow_framework.dylib
      )
    endif()
    set(WASMEDGE_TENSORFLOW_DEPS_TF_LIB
      "${wasmedgetensorflowdeps_SOURCE_DIR}/libtensorflow_cc.2.6.0.dylib"
      "${wasmedgetensorflowdeps_SOURCE_DIR}/libtensorflow_framework.2.6.0.dylib"
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
