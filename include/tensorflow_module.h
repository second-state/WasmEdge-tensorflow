// SPDX-License-Identifier: Apache-2.0
#pragma once

#include "runtime/importobj.h"

namespace SSVM {
namespace Host {

class SSVMTensorflowModule : public Runtime::ImportObject {
public:
  SSVMTensorflowModule();
  ~SSVMTensorflowModule() = default;
};

} // namespace Host
} // namespace SSVM
