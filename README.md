# Second State WebAssembly VM for Tensorflow Extension

The [Second State VM (SSVM)](https://github.com/second-state/ssvm) is a high performance WebAssembly runtime optimized for server side applications. This project provides support for accessing with [Tensorflow C library](https://www.tensorflow.org/install/lang_c).

# Getting Started

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

# And you will need to install llvm for ssvm-aot tools
$ sudo apt install -y \
	llvm-dev \
	liblld-10-dev

# SSVM supports both clang++ and g++ compilers
# You can choose one of them for building this project
$ sudo apt install -y gcc g++
$ sudo apt install -y clang
```

## Get SSVM-Tensorflow Source Code

```bash
$ git clone --recursive git@github.com:second-state/ssvm-tensorflow.git
$ cd ssvm-tensorflow
$ git checkout 0.7.3
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

The executable `build/tools/ssvmc-tensorflow` is the AOT compiler for WASM files.
The executable `build/tools/ssvm-tensorflow` is the runner for executing WASM or compiled WASM.
The executable `build/tools/ssvm-tensorflow-lite` is the runner for executing WASM or compiled WASM with only TensorFlow-lite host functions supported.

## Run SSVM-Tensorflow

```bash
wget https://github.com/second-state/ssvm-tensorflow/releases/download/0.7.3/ssvm-tensorflow-0.7.3-manylinux2014_x86_64.tar.gz
tar -zxvf ssvm-tensorflow-0.7.3-manylinux2014_x86_64.tar.gz
# Download the required shared libraries and make symbolic links.
./download_dependencies_all.sh
LD_LIBRARY_PATH=. ./ssvm-tensorflow
# For developers want to use TensorFlow-Lite only
./download_dependencies_tflite.sh
LD_LIBRARY_PATH=. ./ssvm-tensorflow-lite
```
