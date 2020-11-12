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

# SSVM-Tensorflow requires the JPEG and PNG library
$ sudo apt install -y libjpeg-dev libpng-dev
```

## Get SSVM-Tensorflow Source Code

```bash
$ git clone git@github.com:second-state/ssvm-tensorflow.git
$ cd ssvm-tensorflow
$ git checkout master
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

### Install the required dependencies

```bash
# Install the JPEG and PNG library
(docker)$ apt-get update && apt-get install -y libjpeg-dev libpng-dev
# Install the tensorflow library
(docker)$ wget https://storage.googleapis.com/tensorflow/libtensorflow/libtensorflow-cpu-linux-x86_64-2.3.0.tar.gz
(docker)$ tar -C /usr/local -xzf libtensorflow-cpu-linux-x86_64-2.3.0.tar.gz
(docker)$ ldconfig
```

Please see the [Tensorflow Installation](https://www.tensorflow.org/install/lang_c) for detail.

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
