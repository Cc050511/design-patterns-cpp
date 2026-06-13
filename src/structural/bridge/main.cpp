/**
 * Bridge — 分离抽象与实现
 *
 * 核心结构：Abstraction类 + Implementor接口 + 具体实现 + 组合关系
 * 评测要点：
 *   - 结构：Abstraction类, Implementor类, 组合关系, virtual方法
 *   - 行为：展示抽象操作、实现变化、独立变化
 *   - 输出：包含 "Bridge", "abstraction", "implementation", "independent" 等关键词
 * 评测：python3 scripts/evaluate.py build src
 * 参考：.reference/bridge.cpp
 */

#include <memory>
#include <iostream>

// TODO: 实现此设计模式的所有类

int main() {
    std::cout << "=== Bridge Demo ===\n";
    // TODO: 创建对象并演示设计模式
    std::cout << "Bridge verified successfully.\n";
    return 0;
}
