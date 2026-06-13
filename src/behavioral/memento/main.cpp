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

// TODO: 实现你的 Memento

int main() {
    std::cout << "=== Memento Demo ===\n";
    // TODO
}
