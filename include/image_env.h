// SPDX-License-Identifier: Apache-2.0
#pragma once

#include <cstdint>
#include <utility>
#include <vector>

namespace SSVM {
namespace Host {

class SSVMImageEnvironment {
public:
  std::vector<uint8_t> Res;
};

} // namespace Host
} // namespace SSVM
