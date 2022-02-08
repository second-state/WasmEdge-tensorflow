# SPDX-License-Identifier: Apache-2.0
# SPDX-FileCopyrightText: 2019-2022 Second State INC

if(UNIX AND NOT ANDROID)
  if(CMAKE_SYSTEM_PROCESSOR STREQUAL "x86_64" OR CMAKE_SYSTEM_PROCESSOR STREQUAL "AMD64")
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
endif()

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
  if(UNIX AND NOT ANDROID)
    if(CMAKE_SYSTEM_PROCESSOR STREQUAL "x86_64" OR CMAKE_SYSTEM_PROCESSOR STREQUAL "AMD64")
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
    endif()
  endif()

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

  # FIXME: This is a workaround solution. Linking libwasmedge-tensorflowlite_c.so for Android needs the libtensorflowlite_c.so.
  if(ANDROID)
    if(NOT TENSORFLOW_LITE_LIB)
      FetchContent_Declare(
        wasmedgetensorflowdepslite
        URL      "https://github.com/second-state/WasmEdge-tensorflow-deps/releases/download/${WASMEDGE_DEPS_VERSION}/WasmEdge-tensorflow-deps-TFLite-${WASMEDGE_DEPS_VERSION}-android_aarch64.tar.gz"
        URL_HASH "SHA256=102ad87a6cd7794a72ca3504a046b8960c928ba44c69b1a0587cdb21fe76588f"
      )
      FetchContent_GetProperties(wasmedgetensorflowdepslite)
      if (NOT wasmedgetensorflowdepslite_POPULATED)
        FetchContent_Populate(wasmedgetensorflowdepslite)
      endif()

      set(TENSORFLOW_LITE_LIB
        "${wasmedgetensorflowdepslite_SOURCE_DIR}/libtensorflowlite_c.so"
      )
    endif()

    target_link_libraries(wasmedge-tensorflowlite_c
      PRIVATE
      ${TENSORFLOW_LITE_LIB}
    )
  endif()
endif()
