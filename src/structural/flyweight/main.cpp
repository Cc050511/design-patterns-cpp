/**
 * Flyweight — 共享细粒度对象
 *
 * 核心结构：Flyweight接口 + 具体享元 + FlyweightFactory + 内外状态分离
 * 评测要点：
 *   - 结构：Flyweight类, 状态分离, 共享管理, 对象池
 *   - 行为：展示共享对象、状态分离、节省资源
 *   - 输出：包含 "Flyweight", "share", "intrinsic", "memory" 等关键词
 * 评测：python3 scripts/evaluate.py build src
 * 参考：.reference/flyweight.cpp
 */

#include <memory>
#include <unordered_map>
#include <string>
#include <iostream>

// TODO: 实现此设计模式的所有类

int main() {
    std::cout << "=== Flyweight Demo ===\n";
    // TODO: 创建对象并演示设计模式
    std::cout << "Flyweight verified successfully.\n";
    return 0;
}
