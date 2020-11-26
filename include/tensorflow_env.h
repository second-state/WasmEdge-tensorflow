// SPDX-License-Identifier: Apache-2.0
#pragma once

#include <tensorflow/c/c_api.h>

#include <cstdint>
#include <utility>
#include <vector>

namespace SSVM {
namespace Host {

class SSVMTensorflowEnvironment {
public:
  std::vector<std::pair<std::string, uint32_t>> Inputs;
  std::vector<std::pair<std::string, uint32_t>> Outputs;
  std::vector<TF_Tensor *> InputTensors;
};

} // namespace Host
} // namespace SSVM
