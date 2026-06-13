#include <iostream>
#include <string>

/**
 * Facade — 外观模式
 * ===================
 * 意图: 为子系统中的一组接口提供一个一致的界面 (高层接口)。
 *       Facade 模式定义了一个高层接口，使得子系统更容易使用。
 *
 * 练习要点:
 *   - 子系统由多个复杂类组成 (如 DVD, Projector, Amplifier, Lights)
 *   - Facade 封装子系统的交互流程，提供简单方法 (如 watchMovie())
 *   - 客户端只依赖 Facade，不直接依赖子系统
 *   - Facade 不限制对子系统的直接访问 (需要时可绕过)
 *
 * 参考角色:
 *   Facade (HomeTheaterFacade)
 *   Subsystem classes (DVDPlayer, Projector, Amplifier, Lights)
 */

// ============================================
// 评测检查清单 (Evaluation Checklist)
// ============================================
// 完成本模式后，你的实现应该展示：
//
// 结构要求 (必须包含以下类/接口):
//   ✓ Facade 类 (简化接口)
//   ✓ 多个 Subsystem 复杂类
//   ✓ Facade 委托调用 Subsystem
//
// 行为要求 (运行时输出应展示):
//   ✓ 展示 Facade 简化调用
//   ✓ 展示复杂子系统内部交互
//   ✓ 展示客户端只依赖 Facade
//
// 输出要求:
//   ✓ 输出应包含模式名称: "=== {Pattern} Demo ==="
//   ✓ 输出至少 5 行非空内容
//   ✓ 输出不应包含 "TODO"
//
// 参考实现: .reference/{pattern_name}.cpp
// 评测命令: python3 scripts/evaluate.py build src
// ============================================

// TODO: 实现你的 Facade

int main() {
    std::cout << "=== Facade Demo ===\n";
    // TODO
}
