// SPDX-License-Identifier: Apache-2.0
#pragma once

#include "runtime/importobj.h"

namespace WasmEdge {
namespace Host {

class WasmEdgeTensorflowModule : public Runtime::ImportObject {
public:
  WasmEdgeTensorflowModule();
  ~WasmEdgeTensorflowModule() = default;
};

} // namespace Host
} // namespace WasmEdge
