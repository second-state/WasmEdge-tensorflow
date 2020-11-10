// SPDX-License-Identifier: Apache-2.0
#pragma once

#include <cstdint>
#include <sstream>

namespace SSVM {
namespace Host {

class SSVMTensorflowEnvironment {
public:
  std::vector<std::string> Inputs;
  std::vector<std::string> Outputs;
  std::stringstream Res;
};

} // namespace Host
} // namespace SSVM
