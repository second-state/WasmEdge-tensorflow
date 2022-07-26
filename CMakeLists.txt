# SPDX-License-Identifier: Apache-2.0
# SPDX-FileCopyrightText: 2019-2022 Second State INC

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
  if (CMAKE_GENERATOR STREQUAL Ninja)
    if(CMAKE_COMPILER_IS_GNUCXX)
      list(TRANSFORM CMAKE_C_COMPILE_OPTIONS_IPO REPLACE "^-flto$" "-flto=auto")
      list(TRANSFORM CMAKE_CXX_COMPILE_OPTIONS_IPO REPLACE "^-flto$" "-flto=auto")
    endif()
    set(CMAKE_JOB_POOLS "link=2")
    set(CMAKE_JOB_POOL_LINK link)
  endif()
endif()
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_ENABLE_EXPORTS ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_VISIBILITY_INLINES_HIDDEN ON)
set(CMAKE_SKIP_RPATH ON)

# List of WasmEdge options
option(WASMEDGE_BUILD_TOOLS "Generate wasmedge and wasmedgec tools." OFF)
# Libraries will be built in this project, hence the wasmedge and wasmedgec are not needed.
option(WASMEDGE_BUILD_AOT_RUNTIME "Enable WasmEdge LLVM-based ahead of time compilation runtime." OFF)
# AOT runtime is not needed in this stand-alone project.
option(WASMEDGE_BUILD_SHARED_LIB "Generate the WasmEdge shared library." OFF)
# libwasmedge_c.so is not needed in this stand-alone project.
option(WASMEDGE_TENSORFLOW_BUILD_SHARED_LIB "Generate the libwasmedge-tensorflow_c and libwasmedge-tensorflowlite_c shared libraries." ON)

# WasmEdge dependencies versions
if(NOT WASMEDGE_DEPS_VERSION)
  set(WASMEDGE_DEPS_VERSION "0.10.1-rc.1")
endif()

# Check the build architecture and system.
if(ANDROID)
  if(NOT CMAKE_SYSTEM_PROCESSOR STREQUAL "aarch64")
    message(FATAL_ERROR "Unsupported architecture: ${CMAKE_SYSTEM_PROCESSOR}")
  endif()
elseif(APPLE)
  if(CMAKE_SYSTEM_PROCESSOR STREQUAL "x86_64" OR CMAKE_SYSTEM_PROCESSOR STREQUAL "AMD64")
  else()
    message(FATAL_ERROR "Unsupported architecture: ${CMAKE_SYSTEM_PROCESSOR}")
  endif()
elseif(UNIX)
  if(CMAKE_SYSTEM_PROCESSOR STREQUAL "x86_64" OR CMAKE_SYSTEM_PROCESSOR STREQUAL "AMD64" OR CMAKE_SYSTEM_PROCESSOR STREQUAL "aarch64")
  else()
    message(FATAL_ERROR "Unsupported architecture: ${CMAKE_SYSTEM_PROCESSOR}")
  endif()
else()
  message(FATAL_ERROR "Unsupported system: ${CMAKE_SYSTEM_NAME}")
endif()

# Clone WasmEdge-core
if(NOT WASMEDGE_CORE_PATH)
  include(FetchContent)
  FetchContent_Declare(
    wasmedge
    GIT_REPOSITORY https://github.com/WasmEdge/WasmEdge.git
    GIT_TAG ${WASMEDGE_DEPS_VERSION}
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

message(STATUS "WasmEdge-tensorflow: Set WasmEdge-core source path: ${WASMEDGE_CORE_PATH}")
message(STATUS "WasmEdge-tensorflow: Set WasmEdge-core binary path: ${WASMEDGE_CORE_BIN_PATH}")

# TensorFlow dependencies library
add_subdirectory(utils/WasmEdge-tensorflow-deps)

include_directories(BEFORE
  ${CMAKE_CURRENT_BINARY_DIR}/include
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_subdirectory(include)
add_subdirectory(lib)
