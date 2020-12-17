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
