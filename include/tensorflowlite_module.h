// SPDX-License-Identifier: Apache-2.0
// SPDX-FileCopyrightText: 2019-2022 Second State INC

#pragma once

#include "runtime/instance/module.h"

namespace WasmEdge {
namespace Host {

class WasmEdgeTensorflowLiteModule : public Runtime::Instance::ModuleInstance {
public:
  WasmEdgeTensorflowLiteModule();
  ~WasmEdgeTensorflowLiteModule() = default;
};

} // namespace Host
} // namespace WasmEdge
