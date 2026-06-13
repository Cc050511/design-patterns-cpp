/**
 * Iterator — 迭代器模式
 * ========================
 * 意图: 提供一种方法顺序访问一个聚合对象中各个元素，而又不需暴露该对象的内部表示。
 *
 * 练习要点:
 *   - C++ STL 迭代器即是此模式 (RandomAccess, Bidirectional, Forward…)
 *   - 自定义容器实现 begin() / end()
 *   - Iterator 类重载 operator*, ->, ++, ==, !=
 *   - [可选] 实现 const_iterator, reverse_iterator
 *
 * C++23 可选特性:
 *   - std::generator (协程) 替代手写迭代器，co_yield 懒加载遍历
 *   - std::ranges::contains / std::ranges::fold_left 辅助算法
 *   - std::mdspan 多维数组视图，适合矩阵/网格迭代
 *   - std::print / std::println 格式化输出遍历日志
 *
 * 参考角色:
 *   Aggregate (自定义容器) ← ConcreteAggregate (如 LinkedList<T>)
 *   Iterator — 封装遍历逻辑
 */

#include <iostream>
#include <memory>
#include <string>

// TODO: 实现你的 Iterator

int main() {
    std::cout << "=== Iterator Demo ===\n";
    // TODO
}
