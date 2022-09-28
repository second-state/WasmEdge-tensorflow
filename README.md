# WasmEdge for Tensorflow Extension

The [WasmEdge](https://github.com/WasmEdge/WasmEdge) is a high performance WebAssembly runtime optimized for server side applications. This project provides support for accessing with [Tensorflow C library](https://www.tensorflow.org/install/lang_c).

## Getting Started

### Requirements

The WasmEdge Tensorflow shared library `libwasmedge-tensorflow_c.so` and `libwasmedge-tensorflowlite_c.so` are provided for the `WasmEdge-Tensorflow` extension of the WasmEdge shared library.
The WasmEdge Tensorflow static library `libwasmedgeHostModuleWasmEdgeTensorflow.a` and `libwasmedgeHostModuleWasmEdgeTensorflowLite.a` are provided for statical linking when building executables with CMake.
When linking with `libwasmedge-tensorflow_c.so` and `libwasmedgeHostModuleWasmEdgeTensorflow.a`, the TensorFlow shared libraries `libtensorflow.so` and `libtensorflow_framework.so` are required.
When linking with `libwasmedge-tensorflowlite_c.so` and `libwasmedgeHostModuleWasmEdgeTensorflowLite.a`, the TensorFlow-Lite shared library `libtensorflowlite_c.so` is required.

The official TensorFlow release only provide the TensorFlow shared library.
You can download and install the pre-built shared libraries:

```bash
wget https://github.com/second-state/WasmEdge-tensorflow-deps/releases/download/0.11.1-rc.1/WasmEdge-tensorflow-deps-TF-0.11.1-rc.1-manylinux2014_x86_64.tar.gz
tar -zxvf WasmEdge-tensorflow-deps-TF-0.11.1-rc.1-manylinux2014_x86_64.tar.gz
rm -f WasmEdge-tensorflow-deps-TF-0.11.1-rc.1-manylinux2014_x86_64.tar.gz
ln -sf libtensorflow.so.2.6.0 libtensorflow.so.2
ln -sf libtensorflow.so.2 libtensorflow.so
ln -sf libtensorflow_framework.so.2.6.0 libtensorflow_framework.so.2
ln -sf libtensorflow_framework.so.2 libtensorflow_framework.so
wget https://github.com/second-state/WasmEdge-tensorflow-deps/releases/download/0.11.1-rc.1/WasmEdge-tensorflow-deps-TFLite-0.11.1-rc.1-manylinux2014_x86_64.tar.gz
tar -zxvf WasmEdge-tensorflow-deps-TFLite-0.11.1-rc.1-manylinux2014_x86_64.tar.gz
rm -f WasmEdge-tensorflow-deps-TFLite-0.11.1-rc.1-manylinux2014_x86_64.tar.gz
```

### Prepare the environment

#### Use our docker image (Recommanded)

Our docker image is based on `ubuntu 20.04`.

```bash
docker pull wasmedge/wasmedge
```

#### Or setup the environment manually

Please notice that WasmEdge-Tensorflow requires cmake>=3.11 and libboost>=1.68.

```bash
# Tools and libraries
sudo apt install -y \
    software-properties-common \
    cmake \
    libboost-all-dev

# WasmEdge supports both clang++ and g++ compilers
# You can choose one of them for building this project
sudo apt install -y gcc g++
sudo apt install -y clang
```

### Get WasmEdge-Tensorflow Source Code

```bash
git clone --recursive https://github.com/second-state/WasmEdge-tensorflow.git
cd WasmEdge-tensorflow
git checkout 0.11.1-rc.1
```

### Build WasmEdge-Tensorflow

WasmEdge-Tensorflow depends on WasmEdge-Core, you have to prepare WasmEdge-Core before you build WasmEdge-Tensorflow.
We provides two options for setting up the WasmEdge-Core:

#### Create and Enter the Build Folder

```bash
# After pulling our WasmEdge docker image
docker run -it --rm \
    -v <path/to/your/WasmEdge-tensorflow/source/folder>:/root/WasmEdge-tensorflow \
    wasmedge/wasmedge:latest
# In docker
cd /root/WasmEdge-tensorflow
mkdir -p build && cd build
```

#### Option 1. Use built-in CMakeLists to get WasmEdge-Core (Recommended)

```bash
# In docker
cmake -DCMAKE_BUILD_TYPE=Release .. && make
```

#### Option 2. Use specific version of WasmEdge-Core by giving WASMEDGE_CORE_PATH

```bash
# In docker
cmake -DWASMEDGE_CORE_PATH=<path/to/WasmEdge/source> -DCMAKE_BUILD_TYPE=Release .. && make
```

The shared library `build/lib/libwasmedge-tensorflow_c.so` is the C API to create the `wasmedge-tensorflow` import object.
The header `build/include/wasmedge-tensorflow.h` is the header of the `libwasmedge-tensorflow_c.so` shared library.
The shared library `build/lib/libwasmedge-tensorflowlite_c.so` is the C API to create the `wasmedge-tensorflowlite` import object.
The header `build/include/wasmedge-tensorflowlite.h` is the header of the `libwasmedge-tensorflowlite_c.so` shared library.
The static library `build/lib/libwasmedgeHostModuleWasmEdgeTensorflow.a` is for executables linking in CMake.
The static library `build/lib/libwasmedgeHostModuleWasmEdgeTensorflowLite.a` is for executables linking in CMake.

## WasmEdge-Tensorflow Tools

The tools is moved to the new [repository](https://github.com/second-state/WasmEdge-tensorflow-tools).
