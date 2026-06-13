/**
 * Factory Method — 子类决定创建哪个对象
 *
 * 核心结构：Product接口 + Creator抽象类 + 具体产品和具体工厂
 * 评测要点：
 *   - 结构：Product类, Creator类, virtual createProduct(), override
 *   - 行为：展示创建过程、产品使用、不同产品类型
 *   - 输出：包含 "Factory Method", "create", "Product", "different" 等关键词
 * 评测：python3 scripts/evaluate.py build src
 * 参考：.reference/factory_method.cpp
 */

#include <memory>
#include <iostream>

// TODO: 实现此设计模式的所有类

int main() {
    std::cout << "=== Factory Method Demo ===\n";
    // TODO: 创建对象并演示设计模式
    std::cout << "Factory Method verified successfully.\n";
    return 0;
}
