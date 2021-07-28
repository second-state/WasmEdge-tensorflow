# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.11)
cmake_policy(SET CMP0091 NEW)
project(WasmEdge-Tensorflow)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE RelWithDebInfo)
endif()

set(CMAKE_INTERPROCEDURAL_OPTIMIZATION OFF)
if(CMAKE_BUILD_TYPE STREQUAL Release OR CMAKE_BUILD_TYPE STREQUAL RelWithDebInfo)
  set(CMAKE_INTERPROCEDURAL_OPTIMIZATION ON)
endif()
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fuse-ld=gold")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_ENABLE_EXPORTS ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_VISIBILITY_INLINES_HIDDEN ON)
set(CMAKE_SKIP_RPATH ON)

# List of WasmEdge options
option(WASMEDGE_BUILD_TOOLS "Generate wasmedge and wasmedgec tools." OFF)
option(WASMEDGE_BUILD_AOT_RUNTIME "Enable WasmEdge LLVM-based ahead of time compilation runtime." OFF)
# AOT runtime is not needed in this stand-alone project
option(WASMEDGE_BUILD_SHARED_LIB "Generate the WasmEdge shared library." OFF)
option(WASMEDGE_TENSORFLOW_BUILD_SHARED_LIB "Generate the libwasmedge-tensorflow_c and libwasmedge-tensorflowlite_c shared libraries." ON)

# Clone WasmEdge-core
if(NOT WASMEDGE_CORE_PATH)
  include(FetchContent)
  FetchContent_Declare(
    wasmedge
    GIT_REPOSITORY https://github.com/WasmEdge/WasmEdge.git
    GIT_TAG 0.8.2-rc.2
  )

  FetchContent_GetProperties(wasmedge)
  if(NOT wasmedge_POPULATED)
    message(STATUS "Fetching WasmEdge repository")
    FetchContent_Populate(wasmedge)
    message(STATUS "Fetching WasmEdge repository - done")
  endif()
  add_subdirectory(${wasmedge_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR}/utils/WasmEdge-core)
  set(WASMEDGE_CORE_PATH ${wasmedge_SOURCE_DIR})
  set(WASMEDGE_CORE_BIN_PATH ${CMAKE_CURRENT_BINARY_DIR}/utils/WasmEdge-core)
else()
  get_filename_component(
    WASMEDGE_CORE_PATH "${WASMEDGE_CORE_PATH}"
    REALPATH
    BASE_DIR "${CMAKE_CURRENT_BINARY_DIR}")
  if(NOT WASMEDGE_CORE_BIN_PATH)
    add_subdirectory(${WASMEDGE_CORE_PATH} ${CMAKE_CURRENT_BINARY_DIR}/utils/WasmEdge-core)
    set(WASMEDGE_CORE_BIN_PATH ${CMAKE_CURRENT_BINARY_DIR}/utils/WasmEdge-core)
  else()
    get_filename_component(
      WASMEDGE_CORE_BIN_PATH "${WASMEDGE_CORE_BIN_PATH}"
      REALPATH
      BASE_DIR "${CMAKE_CURRENT_BINARY_DIR}")
  endif()
endif()

message(STATUS "Set WasmEdge-core source path: ${WASMEDGE_CORE_PATH}")
message(STATUS "Set WasmEdge-core binary path: ${WASMEDGE_CORE_BIN_PATH}")

# TensorFlow dependencies library
add_subdirectory(utils/WasmEdge-tensorflow-deps)

include_directories(BEFORE
  ${CMAKE_CURRENT_BINARY_DIR}/include
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_subdirectory(include)
add_subdirectory(lib)
