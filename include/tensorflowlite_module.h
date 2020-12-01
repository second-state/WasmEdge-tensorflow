// SPDX-License-Identifier: Apache-2.0
#pragma once

#include "runtime/importobj.h"

namespace SSVM {
namespace Host {

class SSVMTensorflowLiteModule : public Runtime::ImportObject {
public:
  SSVMTensorflowLiteModule();
  ~SSVMTensorflowLiteModule() = default;
};

} // namespace Host
} // namespace SSVM
