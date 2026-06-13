#include <iostream>
#include <string>

/**
 * Adapter — 适配器模式
 * ======================
 * 意图: 将一个类的接口转换成客户希望的另一个接口。
 *       Adapter 使得原本由于接口不兼容而不能一起工作的类可以一起工作。
 *
 * 练习要点:
 *   - Target (客户期望的接口) — 抽象类
 *   - Adaptee (已有的不兼容类)
 *   - Adapter (适配器) — 两种实现:
 *       1. 对象适配器: 组合 Adaptee 对象
 *       2. 类适配器: 多重继承 Target + Adaptee
 *
 * 参考角色:
 *   Target (IMediaPlayer) ← Adapter (FormatAdapter)
 *   Adaptee (LegacyPlayer)
 */

// ============================================
// 评测检查清单 (Evaluation Checklist)
// ============================================
// 完成本模式后，你的实现应该展示：
//
// 结构要求 (必须包含以下类/接口):
//   ✓ Target 接口 (客户期望的接口)
//   ✓ Adaptee 类 (已有不兼容类)
//   ✓ Adapter 类 (转换接口)
//
// 行为要求 (运行时输出应展示):
//   ✓ 展示通过 Adapter 调用 Target 接口
//   ✓ 展示内部转发到 Adaptee
//   ✓ 展示不兼容接口变得兼容
//
// 输出要求:
//   ✓ 输出应包含模式名称: "=== {Pattern} Demo ==="
//   ✓ 输出至少 5 行非空内容
//   ✓ 输出不应包含 "TODO"
//
// 参考实现: .reference/{pattern_name}.cpp
// 评测命令: python3 scripts/evaluate.py build src
// ============================================

// TODO: 实现你的 Adapter

int main() {
    std::cout << "=== Adapter Demo ===\n";
    // TODO
}
