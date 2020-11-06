include(FindPackageHandleStandardArgs)
unset(TENSORFLOW_FOUND)

find_path(TensorFlow_INCLUDE
        NAMES
        tensorflow/c
        HINTS
        /usr/local/include/tensorflow
        /usr/include/tensorflow)

find_library(TensorFlow_LIB NAMES tensorflow
        HINTS
        /usr/lib
        /usr/local/lib)

# set TensorFlow_FOUND
find_package_handle_standard_args(TensorFlow DEFAULT_MSG TensorFlow_INCLUDE TensorFlow_LIB)

# set external variables for usage in CMakeLists.txt
if(TENSORFLOW_FOUND)
    set(TensorFlow_LIBRARIES ${TensorFlow_LIB})
    set(TensorFlow_INCLUDE_DIR ${TensorFlow_INCLUDE})
else()
    message(FATAL_ERROR "Cannot find libtensorflow.")
endif()
