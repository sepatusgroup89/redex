/**
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once

#include "PassManager.h"

namespace remove_unused_args {

class RemoveArgs {
 public:
  RemoveArgs(const Scope& scope) : m_scope(scope){};
  void run();
  size_t get_num_args_removed() { return m_num_args_removed; }
  size_t get_num_methods_updated() { return m_num_methods_updated; }
  std::deque<uint16_t> compute_live_args(
      DexMethod* method,
      std::vector<IRInstruction*>& dead_insns,
      size_t num_args);

 private:
  const Scope& m_scope;
  std::unordered_map<DexMethod*, std::deque<uint16_t>> m_live_regs_map;
  size_t m_num_args_removed;
  size_t m_num_methods_updated;

  bool update_method_signature(DexMethod* method,
                               std::deque<DexType*> live_args);
  void update_meths_with_unused_args();
  void update_callsite(IRInstruction* instr);
  void update_callsites();
};

class RemoveUnusedArgsPass : public Pass {
 public:
  RemoveUnusedArgsPass() : Pass("RemoveUnusedArgsPass") {}

  virtual void run_pass(DexStoresVector&,
                        ConfigFiles&,
                        PassManager& mgr) override;
};

} // namespace remove_unused_args
