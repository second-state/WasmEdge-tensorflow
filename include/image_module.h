// SPDX-License-Identifier: Apache-2.0
#pragma once

#include "runtime/importobj.h"

namespace SSVM {
namespace Host {

class SSVMImageModule : public Runtime::ImportObject {
public:
  SSVMImageModule();
  ~SSVMImageModule() = default;
};

} // namespace Host
} // namespace SSVM
