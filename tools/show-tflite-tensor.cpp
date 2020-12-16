#include "tensorflow/lite/c/c_api.h"

#include <cstdint>
#include <iostream>
#include <vector>

void printDataType(TfLiteType T) {
  switch (T) {
  case TfLiteType::kTfLiteNoType:
    std::cout << "NoType";
    break;
  case TfLiteType::kTfLiteFloat32:
    std::cout << "Float32";
    break;
  case TfLiteType::kTfLiteInt32:
    std::cout << "Int32";
    break;
  case TfLiteType::kTfLiteUInt8:
    std::cout << "UInt8";
    break;
  case TfLiteType::kTfLiteInt64:
    std::cout << "Int64";
    break;
  case TfLiteType::kTfLiteString:
    std::cout << "String";
    break;
  case TfLiteType::kTfLiteBool:
    std::cout << "Bool";
    break;
  case TfLiteType::kTfLiteInt16:
    std::cout << "Int16";
    break;
  case TfLiteType::kTfLiteComplex64:
    std::cout << "Complex64";
    break;
  case TfLiteType::kTfLiteInt8:
    std::cout << "Int8";
    break;
  case TfLiteType::kTfLiteFloat16:
    std::cout << "Float16";
    break;
  case TfLiteType::kTfLiteFloat64:
    std::cout << "Float64";
    break;
  case TfLiteType::kTfLiteComplex128:
    std::cout << "Complex128";
    break;
  default:
    std::cout << "Unknown";
    break;
  }
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    std::cout << "Usage: ./show-tflite-tensor MODEL.tflite" << std::endl;
    return 0;
  }
  TfLiteModel *model = TfLiteModelCreateFromFile(argv[1]);
  if (model == nullptr) {
    return 0;
  }
  TfLiteInterpreter *interpreter = TfLiteInterpreterCreate(model, nullptr);
  TfLiteInterpreterAllocateTensors(interpreter);
  TfLiteModelDelete(model);

  uint32_t InCnt = TfLiteInterpreterGetInputTensorCount(interpreter);
  uint32_t OutCnt = TfLiteInterpreterGetOutputTensorCount(interpreter);
  std::cout << "Input tensor nums: " << InCnt << std::endl;
  for (uint32_t i = 0; i < InCnt; ++i) {
    TfLiteTensor *input_tensor =
        TfLiteInterpreterGetInputTensor(interpreter, i);
    std::cout << "    Input tensor name: " << TfLiteTensorName(input_tensor)
              << std::endl;
    std::cout << "        dimensions: ";
    if (TfLiteTensorNumDims(input_tensor) > 0) {
      std::cout << "[";
      for (int32_t j = 0; j < TfLiteTensorNumDims(input_tensor); j++) {
        std::cout << TfLiteTensorDim(input_tensor, j);
        if (j < TfLiteTensorNumDims(input_tensor) - 1) {
          std::cout << " , ";
        }
      }
      std::cout << "]" << std::endl;
    } else {
      std::cout << "SCALAR" << std::endl;
    }
    std::cout << "        data type: ";
    printDataType(TfLiteTensorType(input_tensor));
    std::cout << std::endl;
    std::cout << "        tensor byte size: "
              << TfLiteTensorByteSize(input_tensor) << std::endl;
  }

  std::cout << "Output tensor nums: " << OutCnt << std::endl;
  for (uint32_t i = 0; i < OutCnt; ++i) {
    const TfLiteTensor *output_tensor =
        TfLiteInterpreterGetOutputTensor(interpreter, i);
    std::cout << "    Output tensor name: " << TfLiteTensorName(output_tensor)
              << std::endl;
    std::cout << "        dimensions: ";
    if (TfLiteTensorNumDims(output_tensor) > 0) {
      std::cout << "[";
      for (int32_t j = 0; j < TfLiteTensorNumDims(output_tensor); j++) {
        std::cout << TfLiteTensorDim(output_tensor, j);
        if (j < TfLiteTensorNumDims(output_tensor) - 1) {
          std::cout << " , ";
        }
      }
      std::cout << "]" << std::endl;
      ;
    } else {
      std::cout << "SCALAR" << std::endl;
    }
    std::cout << "        data type: ";
    printDataType(TfLiteTensorType(output_tensor));
    std::cout << std::endl;
    std::cout << "        tensor byte size: "
              << TfLiteTensorByteSize(output_tensor) << std::endl;
  }

  TfLiteInterpreterDelete(interpreter);
  return 0;
}
