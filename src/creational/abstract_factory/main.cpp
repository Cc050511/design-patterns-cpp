/**
 * Abstract Factory — 抽象工厂模式
 * =================================
 * 意图: 提供一个创建一系列相关或相互依赖对象的接口，而无需指定它们的具体类。
 *
 * 练习要点:
 *   - 多条产品线 (如 Button + Checkbox)，每条有多个变体 (Win/Mac)
 *   - AbstractFactory 接口声明创建每种产品的方法
 *   - ConcreteFactory (WinFactory, MacFactory) 创建同族产品
 *   - 与 Factory Method 的区别: 抽象工厂创建"一族"产品，工厂方法创建"一个"产品
 *
 * 参考角色:
 *   AbstractFactory (GUIFactory)  ← ConcreteFactory (WinFactory, MacFactory)
 *   AbstractProduct (Button, Checkbox) ← ConcreteProduct (WinButton, MacCheckbox…)
 */

#include <iostream>
#include <memory>

// ============================================
// 评测检查清单 (Evaluation Checklist)
// ============================================
// 完成本模式后，你的实现应该展示：
//
// 结构要求 (必须包含以下类/接口):
//   ✓ AbstractFactory 接口 (多个 create 方法)
//   ✓ ConcreteFactory 实现同族产品
//   ✓ AbstractProduct 接口
//   ✓ ConcreteProduct 实现
//
// 行为要求 (运行时输出应展示):
//   ✓ 展示一族相关产品的创建
//   ✓ 展示不同工厂创建不同产品族
//   ✓ 展示产品配套使用
//
// 输出要求:
//   ✓ 输出应包含模式名称: "=== {Pattern} Demo ==="
//   ✓ 输出至少 5 行非空内容
//   ✓ 输出不应包含 "TODO"
//
// 参考实现: .reference/{pattern_name}.cpp
// 评测命令: python3 scripts/evaluate.py build src
// ============================================

// TODO: 实现你的 Abstract Factory

int main() {
    std::cout << "=== Abstract Factory Demo ===\n";
    // TODO
}
