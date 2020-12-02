// SPDX-License-Identifier: Apache-2.0
#pragma once

#include "common/errcode.h"
#include "runtime/hostfunc.h"

namespace SSVM {
namespace Host {

template <typename T> class SSVMImage : public Runtime::HostFunction<T> {
public:
  SSVMImage() : Runtime::HostFunction<T>(0) {}
};

} // namespace Host
} // namespace SSVM