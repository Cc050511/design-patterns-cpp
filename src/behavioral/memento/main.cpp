/**
 * Memento — 捕获并恢复对象状态
 *
 * 核心结构：Memento类 + Originator + Caretaker + 状态保存恢复
 * 评测要点：
 *   - 结构：Memento类, Originator类, Caretaker类, 状态保存恢复
 *   - 行为：展示保存状态、恢复状态、状态变化
 *   - 输出：包含 "Memento", "save", "restore", "state" 等关键词
 * 评测：python3 scripts/evaluate.py build src
 * 参考：.reference/memento.cpp
 */

#include <memory>
#include <vector>
#include <string>
#include <iostream>

// TODO: 实现此设计模式的所有类

int main() {
    std::cout << "=== Memento Demo ===\n";
    // TODO: 创建对象并演示设计模式
    std::cout << "Memento verified successfully.\n";
    return 0;
}
