# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.11)
project(SSVM-Tensorflow)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE RelWithDebInfo)
endif()

if(CMAKE_BUILD_TYPE STREQUAL Release OR CMAKE_BUILD_TYPE STREQUAL RelWithDebInfo)
  set(CMAKE_INTERPROCEDURAL_OPTIMIZATION ON)
endif()
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fuse-ld=gold")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_ENABLE_EXPORTS ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
option(STATIC_BUILD "Link glibcxx library statically." OFF)
option(BUILD_TOOLS "Generate ssvm and ssvmc tools." OFF)

find_package(Boost "1.68.0" REQUIRED)
find_package(Filesystem REQUIRED Final Experimental)

# Clone required shared libraries
include(FetchContent)
FetchContent_Declare(
  ssvmtensorflowdeps
  URL      https://github.com/second-state/ssvm-tensorflow-deps/releases/download/0.1.0/ssvm-tensorflow-deps-0.1.0-linux-x64.tar.gz
  URL_HASH MD5=5d805f0454ab3f709985d5c6caa4f539
)
FetchContent_GetProperties(ssvmtensorflowdeps)
if (NOT ssvmtensorflowdeps_POPULATED)
  message(STATUS "Downloading dependencies")
  FetchContent_Populate(ssvmtensorflowdeps)
  execute_process(
    COMMAND ${CMAKE_COMMAND} -E create_symlink libtensorflow.so.2.4.0 ${ssvmtensorflowdeps_SOURCE_DIR}/libtensorflow.so.2
    COMMAND ${CMAKE_COMMAND} -E create_symlink libtensorflow.so.2 ${ssvmtensorflowdeps_SOURCE_DIR}/libtensorflow.so
    COMMAND ${CMAKE_COMMAND} -E create_symlink libtensorflow_framework.so.2.4.0 ${ssvmtensorflowdeps_SOURCE_DIR}/libtensorflow_framework.so.2
    COMMAND ${CMAKE_COMMAND} -E create_symlink libtensorflow_framework.so.2 ${ssvmtensorflowdeps_SOURCE_DIR}/libtensorflow_framework.so
  )
  message(STATUS "Downloading dependencies - done")
endif ()
set(SSVM_TENSORFLOW_DEPS_DIR ${ssvmtensorflowdeps_SOURCE_DIR})
set(TENSORFLOW_LIB
  "${ssvmtensorflowdeps_SOURCE_DIR}/libtensorflow.so.2.4.0"
  "${ssvmtensorflowdeps_SOURCE_DIR}/libtensorflow_framework.so.2.4.0"
)
set(TENSORFLOW_LITE_LIB
  "${ssvmtensorflowdeps_SOURCE_DIR}/libtensorflowlite_c.so"
)

# Clone ssvm-core
if(NOT SSVM_CORE_PATH)
  include(FetchContent)
  FetchContent_Declare(
    ssvm
    GIT_REPOSITORY https://github.com/second-state/SSVM.git
    GIT_TAG 0.7.2
  )

  FetchContent_GetProperties(ssvm)
  if (NOT ssvm_POPULATED)
    message(STATUS "Fetching ssvm repository")
    FetchContent_Populate(ssvm)
    message(STATUS "Fetching ssvm repository - done")
  endif ()
  add_subdirectory(${ssvm_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR}/utils/ssvm-core)
  set(SSVM_CORE_SRC_DIR ${ssvm_SOURCE_DIR})
else()
  get_filename_component(
    SSVM_CORE_PATH "${SSVM_CORE_PATH}"
    REALPATH
    BASE_DIR "${CMAKE_CURRENT_BINARY_DIR}")
  add_subdirectory(${SSVM_CORE_PATH} ${CMAKE_CURRENT_BINARY_DIR}/utils/ssvm-core)
  set(SSVM_CORE_SRC_DIR ${SSVM_CORE_PATH})
endif()

# TensorFlow lite static library
add_subdirectory(utils/ssvm-tensorflow-deps)

include_directories(BEFORE
  ${CMAKE_CURRENT_BINARY_DIR}/include
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_subdirectory(include)
add_subdirectory(lib)
add_subdirectory(tools)
