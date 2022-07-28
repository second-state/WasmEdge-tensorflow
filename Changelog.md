### 0.10.1 (2022-07-28)

This is the host function extension for [WasmEdge](https://github.com/WasmEdge/WasmEdge).
Please refer to the [WasmEdge 0.10.1](https://github.com/WasmEdge/WasmEdge/releases/tag/0.10.1) for more details.

Features:

* Update the `WasmEdge` dependency to `0.10.1`.

### 0.10.0 (2022-05-24)

This is the host function extension for [WasmEdge](https://github.com/WasmEdge/WasmEdge).
Please refer to the [WasmEdge 0.10.0](https://github.com/WasmEdge/WasmEdge/releases/tag/0.10.0) for more details.

Breaking changes:

* Renamed C API `WasmEdge_Tensorflow_ImportObjectCreate` to `WasmEdge_Tensorflow_ModuleInstanceCreate`.
* Renamed C API `WasmEdge_Tensorflow_ImportObjectCreateDummy` to `WasmEdge_Tensorflow_ModuleInstanceCreateDummy`.
* Renamed C API `WasmEdge_TensorflowLite_ImportObjectCreate` to `WasmEdge_TensorflowLite_ModuleInstanceCreate`.

Features:

* Update the `WasmEdge` dependency to `0.10.0`.
* Added the Darwin x86_64 support.

### 0.9.1 (2022-02-10)

This is the host function extension for [WasmEdge](https://github.com/WasmEdge/WasmEdge).
Please refer to the [WasmEdge 0.9.1](https://github.com/WasmEdge/WasmEdge/releases/tag/0.9.1) for more details.

Features:

* Added the copyright text.
* Update the `WasmEdge` dependency to `0.9.1`.
* Added the Linux aarch64 support.
* Added the Android aarch64 support.

### 0.9.0 (2021-12-09)

This is the host function extension for [WasmEdge](https://github.com/WasmEdge/WasmEdge).
Please refer to the [WasmEdge 0.9.0](https://github.com/WasmEdge/WasmEdge/releases/tag/0.9.0) for more details.

Breaking changes:

* Moved the C-API headers `wasmedge-tensorflow.h` and `wasmedge-tensorflowlite.h` into the `wasmedge` folder.

Features:

* Update the `WasmEdge` dependency to `0.9.0`.

### 0.8.2 (2021-09-06)

This is the host function extension for [WasmEdge](https://github.com/WasmEdge/WasmEdge).
Please refer to the [WasmEdge 0.8.2](https://github.com/WasmEdge/WasmEdge/releases/tag/0.8.2) for more details.

Features:

* Update the `WasmEdge` dependency to `0.8.2`.
* Modified the CMake option `BUILD_SHARED_LIB` to `WASMEDGE_TENSORFLOW_BUILD_SHARED_LIB` for enabling compilation of the shared library (`ON` by default).

### 0.8.1 (2021-06-22)

This is the host function extension for [WasmEdge](https://github.com/WasmEdge/WasmEdge).
Please refer to the [WasmEdge 0.8.1](https://github.com/WasmEdge/WasmEdge/releases/tag/0.8.1) for more details.

Features:

* Update the `WasmEdge` dependency to `0.8.1`.

### 0.8.0 (2021-05-14)

This is the host function extension for [WasmEdge](https://github.com/WasmEdge/WasmEdge).
Please refer to the [WasmEdge 0.8.0](https://github.com/WasmEdge/WasmEdge/releases/tag/0.8.0) for more details.

Features:

* Renamed this project to `WasmEdge-tensorflow` and updated the `WasmEdge` dependency.
* Added `wasmedge-tensorflow` and `wasmedge-tensorflowlite` C API shared library.
* Added CMake option `BUILD_SHARED_LIB` to enable compiling the shared library (`ON` by default).
* Added release CI.

Tools:

* Remove tools. The tools will be in the new [repository](https://github.com/second-state/WasmEdge-tensorflow-tools).

### 0.7.3 (2021-02-03)

This is a extension release for updating `ssvm-core`.

Features:

* Update `ssvm-core` to version 0.7.3.
  * Please refer to the [SSVM 0.7.3](https://github.com/second-state/SSVM/releases/tag/0.7.3) for more details.

Tools:

* `download_dependencies_tf.sh` is the script to download and extract the required shared libraries of `libtensorflow` and `libtensorflow_framework`.
* `download_dependencies_tflite.sh` is the script to download and extract the required shared libraries for only `ssvm-tensorflow-lite` tool.
* `download_dependencies_all.sh` is the script to download and extract all the required shared libraries.

### 0.7.2 (2020-12-24)

This is a extension release for updating `ssvm-core`.

Features:

* Update `ssvm-core` to version 0.7.2.
  * Please refer to the [SSVM 0.7.2](https://github.com/second-state/SSVM/releases/tag/0.7.2) for more details.

### 0.1.1 (2020-12-22)

This is a extension release for the `ssvm-tensorflow-lite` tool.

Tools:

* `ssvm-tensorflow-lite` is the SSVM runner for executing WASM or compiled WASM with only tensorflow-lite extensions.
* `download_dependencies_lite.sh` is the script to download and extract the required shared libraries for only `ssvm-tensorflow-lite` tool.

### 0.1.0 (2020-12-17)

Features:

* Image processing host function extensions of WASM
  * Support reading JPEG and PNG from buffer.
  * Support the rgb8 and rgb32f normalized formats.
  * Support image resizing.
* TensorFlow and TensorFlow-Lite host function extension of WASM
  * Support creating TensorFlow and TensorFlow-Lite graphs from model buffer.
  * Support running models with input tensors.

Tools:

* `ssvmc-tensorflow` is the AOT compiler to compile WASM files into binaries.
* `ssvm-tensorflow` is the SSVM runner for executing WASM or compiled WASM with tensorflow extensions.
* `show-tflite-tensor` is the tool to list the input and output tensors information of a TensorFlow-Lite model.
* `download_dependencies.sh` is the script to download and extract the required shared libraries.
