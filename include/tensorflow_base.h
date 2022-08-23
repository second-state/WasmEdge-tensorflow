// SPDX-License-Identifier: Apache-2.0
// SPDX-FileCopyrightText: 2019-2022 Second State INC

#pragma once

#include <cstdint>
#include <utility>
#include <vector>

#include "tensorflow/c/c_api.h"

#include "common/errcode.h"
#include "runtime/callingframe.h"
#include "runtime/hostfunc.h"

namespace WasmEdge {
namespace Host {

struct WasmEdgeTensorflowContext {
  WasmEdgeTensorflowContext() { Stat = TF_NewStatus(); }
  ~WasmEdgeTensorflowContext() {
    if (GraphOpts) {
      TF_DeleteImportGraphDefOptions(GraphOpts);
    }
    if (Buffer) {
      TF_DeleteBuffer(Buffer);
    }
    if (Graph) {
      TF_DeleteGraph(Graph);
    }
    if (SessionOpts) {
      TF_DeleteSessionOptions(SessionOpts);
    }
    if (Session) {
      TF_CloseSession(Session, Stat);
      TF_DeleteSession(Session, Stat);
    }
    TF_DeleteStatus(Stat);
    for (uint32_t I = 0; I < InputTensors.size(); ++I) {
      if (InputTensors[I]) {
        TF_DeleteTensor(InputTensors[I]);
      }
    }
    for (uint32_t I = 0; I < OutputTensors.size(); ++I) {
      if (OutputTensors[I]) {
        TF_DeleteTensor(OutputTensors[I]);
      }
    }
  }

  TF_Status *Stat;
  TF_ImportGraphDefOptions *GraphOpts = nullptr;
  TF_Buffer *Buffer = nullptr;
  TF_Graph *Graph = nullptr;
  TF_SessionOptions *SessionOpts = nullptr;
  TF_Session *Session = nullptr;
  std::vector<std::pair<std::string, uint32_t>> InputNames;
  std::vector<std::pair<std::string, uint32_t>> OutputNames;
  std::vector<TF_Output> Inputs;
  std::vector<TF_Output> Outputs;
  std::vector<TF_Tensor *> InputTensors;
  std::vector<TF_Tensor *> OutputTensors;
};

template <typename T>
class WasmEdgeTensorflow : public Runtime::HostFunction<T> {
public:
  WasmEdgeTensorflow() : Runtime::HostFunction<T>(0) {}
};

} // namespace Host
} // namespace WasmEdge
