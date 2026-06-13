/**
 * Visitor — 对一组对象执行新操作
 *
 * 核心结构：Visitor接口 + Element接口 + accept/visit方法 + 双重分发
 * 评测要点：
 *   - 结构：Visitor类, Element类, accept/visit方法, 双重分发
 *   - 行为：展示访问过程、被访问对象、新操作
 *   - 输出：包含 "Visitor", "visit", "element", "operation" 等关键词
 * 评测：python3 scripts/evaluate.py build src
 * 参考：.reference/visitor.cpp
 */

#include <memory>
#include <string>
#include <iostream>

// TODO: 实现此设计模式的所有类

int main() {
    std::cout << "=== Visitor Demo ===\n";
    // TODO: 创建对象并演示设计模式
    std::cout << "Visitor verified successfully.\n";
    return 0;
}
