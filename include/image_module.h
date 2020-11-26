// SPDX-License-Identifier: Apache-2.0
#pragma once

#include "image_env.h"
#include "runtime/importobj.h"

namespace SSVM {
namespace Host {

class SSVMImageModule : public Runtime::ImportObject {
public:
  SSVMImageModule();
  ~SSVMImageModule() = default;

private:
  SSVMImageEnvironment Env;
};

} // namespace Host
} // namespace SSVM
