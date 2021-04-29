# Second State WebAssembly VM for Tensorflow Extension

The [Second State VM (SSVM)](https://github.com/second-state/ssvm) is a high performance WebAssembly runtime optimized for server side applications. This project provides support for accessing with [Tensorflow C library](https://www.tensorflow.org/install/lang_c).

# Getting Started

## Requirements

The SSVM Tensorflow shared library `libssvm-tensorflow_c.so` and `libssvm-tensorflowlite_c.so` are provided for the SSVM-Tensorflow extension of the SSVM shared library.
The SSVM Tensorflow static library `libssvmHostModuleSSVMTensorflow.a` and `libssvmHostModuleSSVMTensorflowLite.a` are provided for statical linking when building executables with CMake.
When linking with `libssvm-tensorflow_c.so` and `libssvmHostModuleSSVMTensorflow.a`, the TensorFlow shared libraries `libtensorflow.so` and `libtensorflow_framework.so` are required.
When linking with `libssvm-tensorflowlite_c.so` and `libssvmHostModuleSSVMTensorflowLite.a`, the TensorFlow-Lite shared library `libtensorflowlite_c.so` is required.

The official TensorFlow release only provide the TensorFlow shared library.
You can download and install the pre-built shared libraries:

```bash
$ wget https://github.com/second-state/ssvm-tensorflow-deps/releases/download/0.7.3/ssvm-tensorflow-deps-TF-0.7.3-manylinux2014_x86_64.tar.gz
$ tar -zxvf ssvm-tensorflow-deps-TF-0.7.3-manylinux2014_x86_64.tar.gz
$ rm -f ssvm-tensorflow-deps-TF-0.7.3-manylinux2014_x86_64.tar.gz
$ ln -sf libtensorflow.so.2.4.0 libtensorflow.so.2
$ ln -sf libtensorflow.so.2 libtensorflow.so
$ ln -sf libtensorflow_framework.so.2.4.0 libtensorflow_framework.so.2
$ ln -sf libtensorflow_framework.so.2 libtensorflow_framework.so
$ wget https://github.com/second-state/ssvm-tensorflow-deps/releases/download/0.7.3/ssvm-tensorflow-deps-TFLite-0.7.3-manylinux2014_x86_64.tar.gz
$ tar -zxvf ssvm-tensorflow-deps-TFLite-0.7.3-manylinux2014_x86_64.tar.gz
$ rm -f ssvm-tensorflow-deps-TFLite-0.7.3-manylinux2014_x86_64.tar.gz
```

## Prepare the environment

### Use our docker image (Recommanded)

Our docker image is based on `ubuntu 20.04`.

```bash
$ docker pull secondstate/ssvm
```

### Or setup the environment manually

Please notice that SSVM-Tensorflow requires cmake>=3.11 and libboost>=1.68.

```bash
# Tools and libraries
$ sudo apt install -y \
	software-properties-common \
	cmake \
	libboost-all-dev

# SSVM supports both clang++ and g++ compilers
# You can choose one of them for building this project
$ sudo apt install -y gcc g++
$ sudo apt install -y clang
```

## Get SSVM-Tensorflow Source Code

```bash
$ git clone --recursive git@github.com:second-state/ssvm-tensorflow.git
$ cd ssvm-tensorflow
$ git checkout 0.8.0-rc1
```

## Build SSVM-Tensorflow

SSVM-Tensorflow depends on SSVM-Core, you have to prepare SSVM-Core before you build SSVM-Tensorflow.
We provides two options for setting up the SSVM-Core:

### Create and Enter the Build Folder

```bash
# After pulling our ssvm docker image
$ docker run -it --rm \
    -v <path/to/your/ssvm-tensorflow/source/folder>:/root/ssvm-tensorflow \
    secondstate/ssvm:latest
(docker)$ cd /root/ssvm-tensorflow
(docker)$ mkdir -p build && cd build
```

### Option 1. Use built-in CMakeLists to get SSVM-Core (Recommended)

```bash
(docker)$ cmake -DCMAKE_BUILD_TYPE=Release .. && make
```

### Option 2. Use specific version of SSVM-Core by giving SSVM_CORE_PATH

```bash
(docker)$ cmake -DSSVM_CORE_PATH=<path/to/ssvm/source> -DCMAKE_BUILD_TYPE=Release .. && make
```

The shared library `build/lib/libssvm-tensorflow_c.so` is the C API to create `ssvm-tensorflow` import object.
The header `build/include/ssvm-tensorflow.h` is the header of the `libssvm-tensorflow_c.so` shared library.
The shared library `build/lib/libssvm-tensorflowlite_c.so` is the C API to create `ssvm-tensorflowlite` import object.
The header `build/include/ssvm-tensorflowlite.h` is the header of the `libssvm-tensorflowlite_c.so` shared library.
The static library `build/lib/libssvmHostModuleSSVMTensorflow.a` is for executables linking in CMake.
The static library `build/lib/libssvmHostModuleSSVMTensorflowLite.a` is for executables linking in CMake.

# SSVM-Tensorflow Tools

The tools is moved to the new [repository](https://github.com/second-state/ssvm-tensorflow-tools).
