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

// ============================================
// 评测检查清单 (Evaluation Checklist)
// ============================================
// 完成本模式后，你的实现应该展示：
//
// 结构要求 (必须包含以下类/接口):
//   ✓ Strategy 接口 (algorithm 方法)
//   ✓ ConcreteStrategy 不同算法
//   ✓ Context 上下文
//
// 行为要求 (运行时输出应展示):
//   ✓ 展示运行时切换算法
//   ✓ 展示不同策略不同结果
//   ✓ 展示策略独立变化
//
// 输出要求:
//   ✓ 输出应包含模式名称: "=== {Pattern} Demo ==="
//   ✓ 输出至少 5 行非空内容
//   ✓ 输出不应包含 "TODO"
//
// 参考实现: .reference/{pattern_name}.cpp
// 评测命令: python3 scripts/evaluate.py build src
// ============================================

// TODO: 实现你的 Strategy

int main() {
    std::cout << "=== Strategy Demo ===\n";
    // TODO
}
