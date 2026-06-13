/**
 * Command — 将请求封装为对象
 *
 * 核心结构：Command接口 + 具体命令 + Receiver + Invoker（支持undo）
 * 评测要点：
 *   - 结构：Command类, execute(), undo(), Receiver/Invoker
 *   - 行为：展示执行命令、撤销命令、命令队列/历史
 *   - 输出：包含 "Command", "execute", "undo", "queue" 等关键词
 * 评测：python3 scripts/evaluate.py build src
 * 参考：.reference/command.cpp
 */

#include <memory>
#include <iostream>

// TODO: 实现此设计模式的所有类

int main() {
    std::cout << "=== Command Demo ===\n";
    // TODO: 创建对象并演示设计模式
    std::cout << "Command verified successfully.\n";
    return 0;
}
