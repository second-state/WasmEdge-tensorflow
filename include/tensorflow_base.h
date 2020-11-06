// SPDX-License-Identifier: Apache-2.0
#pragma once

#include "common/errcode.h"
#include "runtime/hostfunc.h"
#include "tensorflow_env.h"

namespace SSVM {
namespace Host {

template <typename T> class SSVMTensorflow : public Runtime::HostFunction<T> {
public:
  SSVMTensorflow(SSVMTensorflowEnvironment &HostEnv)
      : Runtime::HostFunction<T>(0), Env(HostEnv) {}

protected:
  SSVMTensorflowEnvironment &Env;
};

} // namespace Host
} // namespace SSVM