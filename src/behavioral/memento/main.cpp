/**
 * Memento — 备忘录模式
 * ======================
 * 意图: 在不破坏封装性的前提下，捕获一个对象的内部状态，
 *       并在该对象之外保存这个状态。这样以后就可将该对象恢复到原先保存的状态。
 *
 * 练习要点:
 *   - Memento: 不可变的值对象，只暴露状态给 Originator
 *   - Originator: 创建 Memento (save) 并从 Memento 恢复 (restore)
 *   - Caretaker: 管理 Memento 历史 (如 undo 栈)
 *   - 关键: Memento 不暴露 Originator 的封装细节
 *
 * 参考角色:
 *   Originator (Editor) — 被保存状态的对象
 *   Memento (EditorState) — 快照
 *   Caretaker (History) — 管理快照的栈
 */

#include <iostream>
#include <memory>
#include <string>

// ============================================
// 评测检查清单 (Evaluation Checklist)
// ============================================
// 完成本模式后，你的实现应该展示：
//
// 结构要求 (必须包含以下类/接口):
//   ✓ Memento 备忘录 (不暴露 Originator 细节)
//   ✓ Originator 原发器
//   ✓ Caretaker 管理者
//
// 行为要求 (运行时输出应展示):
//   ✓ 展示保存状态
//   ✓ 展示恢复状态
//   ✓ 展示不破坏封装
//
// 输出要求:
//   ✓ 输出应包含模式名称: "=== {Pattern} Demo ==="
//   ✓ 输出至少 5 行非空内容
//   ✓ 输出不应包含 "TODO"
//
// 参考实现: .reference/{pattern_name}.cpp
// 评测命令: python3 scripts/evaluate.py build src
// ============================================

// TODO: 实现你的 Memento

int main() {
    std::cout << "=== Memento Demo ===\n";
    // TODO
}
