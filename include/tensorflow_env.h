// SPDX-License-Identifier: Apache-2.0
#pragma once

#include <cstdint>
#include <utility>
#include <vector>

namespace SSVM {
namespace Host {

class SSVMTensorflowEnvironment {
public:
  std::vector<std::pair<std::string, uint32_t>> Inputs;
  std::vector<std::pair<std::string, uint32_t>> Outputs;
  std::vector<std::vector<int64_t>> InputDims;
  std::vector<std::vector<uint8_t>> Res;
};

} // namespace Host
} // namespace SSVM
