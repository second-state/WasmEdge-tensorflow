// SPDX-License-Identifier: Apache-2.0
#pragma once

#include <cstdint>
#include <utility>
#include <vector>

#include "tensorflow/lite/c/c_api.h"

#include "common/errcode.h"
#include "runtime/hostfunc.h"

namespace WasmEdge {
namespace Host {

struct WasmEdgeTensorflowLiteContext {
  WasmEdgeTensorflowLiteContext() = default;
  ~WasmEdgeTensorflowLiteContext() {
    if (Interp) {
      TfLiteInterpreterDelete(Interp);
    }
  }
  TfLiteInterpreter *Interp = nullptr;
};

template <typename T>
class WasmEdgeTensorflowLite : public Runtime::HostFunction<T> {
public:
  WasmEdgeTensorflowLite() : Runtime::HostFunction<T>(0) {}
};

} // namespace Host
} // namespace WasmEdge