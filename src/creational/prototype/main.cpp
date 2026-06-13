/**
 * Prototype — 克隆已有对象
 *
 * 核心结构：Prototype接口 + 具体原型 + clone方法 + 原型管理
 * 评测要点：
 *   - 结构：Prototype类, clone()方法, virtual, 原型管理
 *   - 行为：展示克隆过程、原始对象、新实例（地址不同）
 *   - 输出：包含 "Prototype", "clone", "original", "new" 等关键词
 * 评测：python3 scripts/evaluate.py build src
 * 参考：.reference/prototype.cpp
 */

#include <memory>
#include <unordered_map>
#include <string>
#include <iostream>

// TODO: 实现此设计模式的所有类

int main() {
    std::cout << "=== Prototype Demo ===\n";
    // TODO: 创建对象并演示设计模式
    std::cout << "Prototype verified successfully.\n";
    return 0;
}
