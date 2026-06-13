/**
 * Adapter — 转换接口以兼容
 *
 * 核心结构：Target接口 + Adaptee类 + Adapter类（继承或组合）
 * 评测要点：
 *   - 结构：Adapter类, Target接口, Adaptee类, 适配方法
 *   - 行为：展示适配过程、不兼容接口、适配成功
 *   - 输出：包含 "Adapter", "adapt", "compatible", "works" 等关键词
 * 评测：python3 scripts/evaluate.py build src
 * 参考：.reference/adapter.cpp
 */

#include <memory>
#include <iostream>

// TODO: 实现此设计模式的所有类

int main() {
    std::cout << "=== Adapter Demo ===\n";
    // TODO: 创建对象并演示设计模式
    std::cout << "Adapter verified successfully.\n";
    return 0;
}
