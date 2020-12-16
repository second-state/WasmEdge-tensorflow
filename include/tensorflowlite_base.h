// SPDX-License-Identifier: Apache-2.0
#pragma once

#include <cstdint>
#include <utility>
#include <vector>

#include "tensorflow/lite/c/c_api.h"

#include "common/errcode.h"
#include "runtime/hostfunc.h"

namespace SSVM {
namespace Host {

struct SSVMTensorflowLiteContext {
  SSVMTensorflowLiteContext() = default;
  ~SSVMTensorflowLiteContext() {
    if (Interp) {
      TfLiteInterpreterDelete(Interp);
    }
  }
  TfLiteInterpreter *Interp = nullptr;
};

template <typename T>
class SSVMTensorflowLite : public Runtime::HostFunction<T> {
public:
  SSVMTensorflowLite() : Runtime::HostFunction<T>(0) {}
};

} // namespace Host
} // namespace SSVM