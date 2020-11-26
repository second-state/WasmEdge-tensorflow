// SPDX-License-Identifier: Apache-2.0
#pragma once

#include "common/errcode.h"
#include "image_env.h"
#include "runtime/hostfunc.h"

namespace SSVM {
namespace Host {

template <typename T> class SSVMImage : public Runtime::HostFunction<T> {
public:
  SSVMImage(SSVMImageEnvironment &HostEnv)
      : Runtime::HostFunction<T>(0), Env(HostEnv) {}

protected:
  SSVMImageEnvironment &Env;
};

} // namespace Host
} // namespace SSVM