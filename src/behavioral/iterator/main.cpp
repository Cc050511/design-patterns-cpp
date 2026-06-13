/**
 * Iterator — 顺序访问集合元素
 *
 * 核心结构：Iterator接口 + Aggregate接口 + 具体迭代器 + 集合
 * 评测要点：
 *   - 结构：Iterator类, Aggregate类, 遍历方法, begin/end
 *   - 行为：展示遍历过程、访问元素、顺序访问
 *   - 输出：包含 "Iterator", "iterate", "element", "sequential" 等关键词
 * 评测：python3 scripts/evaluate.py build src
 * 参考：.reference/iterator.cpp
 */

#include <memory>
#include <vector>
#include <iostream>

// TODO: 实现此设计模式的所有类

int main() {
    std::cout << "=== Iterator Demo ===\n";
    // TODO: 创建对象并演示设计模式
    std::cout << "Iterator verified successfully.\n";
    return 0;
}
