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
option(BUILD_TOOLS "Generate ssvm and ssvmc tools." OFF)
option(BUILD_TOOLS_SSVM_TENSORFLOW "Generate ssvm-tensorflow tools." ON)

find_package(Boost "1.68.0" REQUIRED)
find_package(Filesystem REQUIRED Final Experimental)

# Clone required shared libraries
include(FetchContent)
FetchContent_Declare(
  ssvmtensorflowdeps
  URL      https://github.com/second-state/ssvm-tensorflow-deps/releases/download/0.7.3/ssvm-tensorflow-deps-TF-0.7.3-manylinux2014_x86_64.tar.gz
  URL_HASH MD5=a5a98e7efd60ffaf4309636015c85b85
)
FetchContent_GetProperties(ssvmtensorflowdeps)
if (NOT ssvmtensorflowdeps_POPULATED)
  message(STATUS "Downloading dependency: libtensorflow")
  FetchContent_Populate(ssvmtensorflowdeps)
  execute_process(
    COMMAND ${CMAKE_COMMAND} -E create_symlink libtensorflow.so.2.4.0 ${ssvmtensorflowdeps_SOURCE_DIR}/libtensorflow.so.2
    COMMAND ${CMAKE_COMMAND} -E create_symlink libtensorflow.so.2 ${ssvmtensorflowdeps_SOURCE_DIR}/libtensorflow.so
    COMMAND ${CMAKE_COMMAND} -E create_symlink libtensorflow_framework.so.2.4.0 ${ssvmtensorflowdeps_SOURCE_DIR}/libtensorflow_framework.so.2
    COMMAND ${CMAKE_COMMAND} -E create_symlink libtensorflow_framework.so.2 ${ssvmtensorflowdeps_SOURCE_DIR}/libtensorflow_framework.so
  )
  message(STATUS "Downloading dependency: libtensorflow - done")
endif ()
FetchContent_Declare(
  ssvmtensorflowdepslite
  URL      https://github.com/second-state/ssvm-tensorflow-deps/releases/download/0.7.3/ssvm-tensorflow-deps-TFLite-0.7.3-manylinux2014_x86_64.tar.gz
  URL_HASH MD5=365cb588e15b7db4ba8441cd1d84a6bf
)
FetchContent_GetProperties(ssvmtensorflowdepslite)
if (NOT ssvmtensorflowdepslite_POPULATED)
  message(STATUS "Downloading dependency: libtensorflowlite")
  FetchContent_Populate(ssvmtensorflowdepslite)
  message(STATUS "Downloading dependency: libtensorflowlite - done")
endif ()

set(TENSORFLOW_LIB
  "${ssvmtensorflowdeps_SOURCE_DIR}/libtensorflow.so.2.4.0"
  "${ssvmtensorflowdeps_SOURCE_DIR}/libtensorflow_framework.so.2.4.0"
)
set(TENSORFLOW_LITE_LIB
  "${ssvmtensorflowdepslite_SOURCE_DIR}/libtensorflowlite_c.so"
)

# Clone ssvm-core
if(NOT SSVM_CORE_PATH)
  include(FetchContent)
  FetchContent_Declare(
    ssvm
    GIT_REPOSITORY https://github.com/second-state/SSVM.git
    GIT_TAG 0.7.3
  )

  FetchContent_GetProperties(ssvm)
  if(NOT ssvm_POPULATED)
    message(STATUS "Fetching ssvm repository")
    FetchContent_Populate(ssvm)
    message(STATUS "Fetching ssvm repository - done")
  endif()
  add_subdirectory(${ssvm_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR}/utils/ssvm-core)
  set(SSVM_CORE_PATH ${ssvm_SOURCE_DIR})
  set(SSVM_CORE_BIN_PATH ${CMAKE_CURRENT_BINARY_DIR}/utils/ssvm-core)
else()
  get_filename_component(
    SSVM_CORE_PATH "${SSVM_CORE_PATH}"
    REALPATH
    BASE_DIR "${CMAKE_CURRENT_BINARY_DIR}")
  if(NOT SSVM_CORE_BIN_PATH)
    add_subdirectory(${SSVM_CORE_PATH} ${CMAKE_CURRENT_BINARY_DIR}/utils/ssvm-core)
    set(SSVM_CORE_BIN_PATH ${CMAKE_CURRENT_BINARY_DIR}/utils/ssvm-core)
  else()
    get_filename_component(
      SSVM_CORE_BIN_PATH "${SSVM_CORE_BIN_PATH}"
      REALPATH
      BASE_DIR "${CMAKE_CURRENT_BINARY_DIR}")
  endif()
endif()

# Clone ssvm-image
if(NOT SSVM_IMAGE_PATH)
  include(FetchContent)
  FetchContent_Declare(
    ssvm_image
    GIT_REPOSITORY https://github.com/second-state/ssvm-image.git
    GIT_TAG master
  )

  FetchContent_GetProperties(ssvm_image)
  if(NOT ssvm_image_POPULATED)
    message(STATUS "Fetching ssvm-image repository")
    FetchContent_Populate(ssvm_image)
    message(STATUS "Fetching ssvm-image repository - done")
  endif()
  add_subdirectory(${ssvm_image_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR}/utils/ssvm-image)
  set(SSVM_IMAGE_PATH ${ssvm_image_SOURCE_DIR})
  set(SSVM_IMAGE_BIN_PATH ${CMAKE_CURRENT_BINARY_DIR}/utils/ssvm-image)
else()
  get_filename_component(
    SSVM_IMAGE_PATH "${SSVM_IMAGE_PATH}"
    REALPATH
    BASE_DIR "${CMAKE_CURRENT_BINARY_DIR}")
  if(NOT SSVM_IMAGE_BIN_PATH)
    add_subdirectory(${SSVM_IMAGE_PATH} ${CMAKE_CURRENT_BINARY_DIR}/utils/ssvm-image)
    set(SSVM_IMAGE_BIN_PATH ${CMAKE_CURRENT_BINARY_DIR}/utils/ssvm-image)
  else()
    get_filename_component(
      SSVM_IMAGE_BIN_PATH "${SSVM_IMAGE_BIN_PATH}"
      REALPATH
      BASE_DIR "${CMAKE_CURRENT_BINARY_DIR}")
  endif()
endif()

message(STATUS "Set ssvm-core source path: ${SSVM_CORE_PATH}")
message(STATUS "Set ssvm-core binary path: ${SSVM_CORE_BIN_PATH}")
message(STATUS "Set ssvm-image source path: ${SSVM_IMAGE_PATH}")
message(STATUS "Set ssvm-image binary path: ${SSVM_IMAGE_BIN_PATH}")

# TensorFlow dependencies library
add_subdirectory(utils/ssvm-tensorflow-deps)

include_directories(BEFORE
  ${CMAKE_CURRENT_BINARY_DIR}/include
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)
include_directories(BEFORE
  ${SSVM_IMAGE_BIN_PATH}/include
  ${SSVM_IMAGE_PATH}/include
)

add_subdirectory(include)
add_subdirectory(lib)
add_subdirectory(tools)
