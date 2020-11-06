// SPDX-License-Identifier: Apache-2.0
#pragma once

#include "runtime/importobj.h"
#include "tensorflow_env.h"

namespace SSVM {
namespace Host {

class SSVMTensorflowModule : public Runtime::ImportObject {
public:
  SSVMTensorflowModule();
  ~SSVMTensorflowModule() = default;

private:
  SSVMTensorflowEnvironment Env;
};

} // namespace Host
} // namespace SSVM
