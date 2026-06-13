/**
 * Strategy — 策略模式
 * =====================
 * 意图: 定义一系列的算法，把它们一个个封装起来，并且使它们可相互替换。
 *       策略模式使得算法可独立于使用它的客户而变化。
 *
 * 练习要点:
 *   - Strategy 接口: 声明算法方法 (如 sort())
 *   - ConcreteStrategy: 实现不同算法 (如 QuickSort, MergeSort, BubbleSort)
 *   - Context: 持有 Strategy*，委托算法调用
 *   - 客户端在运行时切换 Strategy
 *
 * C++23 可选特性:
 *   - std::move_only_function 替代 std::function 绑定只移 lambda
 *   - std::expected 错误处理 (算法返回 expected<Result, Error>)
 *   - std::ranges 算法 (sort, fold_left 等) 简化策略实现
 *   - if constexpr 编译期策略选择 (替代 CRTP 部分场景)
 *   - std::print / std::println 格式化输出算法结果
 *
 * 参考角色:
 *   Strategy (SortStrategy) ← ConcreteStrategy (QuickSort, MergeSort)
 *   Context (Sorter) — 持有 Strategy&，对外提供 sort()
 *
 * 与 State 的区别: 见 state/main.cpp 头部注释
 */

#include <iostream>
#include <memory>
#include <vector>

// TODO: 实现你的 Strategy

int main() {
    std::cout << "=== Strategy Demo ===\n";
    // TODO
}
