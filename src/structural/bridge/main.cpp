/**
 * Bridge — 桥接模式
 * ===================
 * 意图: 将抽象部分与它的实现部分分离，使它们都可以独立地变化。
 *
 * 练习要点:
 *   - Abstraction 持有 Implementor* (桥接)
 *   - Implementor 接口定义底层操作
 *   - 两者可独立扩展: 新增 Abstraction 子类不影响 Implementor，反之亦然
 *   - 关键: 用组合替代多层继承 (避免类爆炸)
 *
 * 参考角色:
 *   Abstraction (RemoteControl) ← RefinedAbstraction (AdvancedRemote)
 *   Implementor (Device) ← ConcreteImplementor (TV, Radio)
 */

#include <iostream>
#include <memory>
#include <string>

// ============================================
// 评测检查清单 (Evaluation Checklist)
// ============================================
// 完成本模式后，你的实现应该展示：
//
// 结构要求 (必须包含以下类/接口):
//   ✓ Abstraction 抽象部分
//   ✓ Implementor 实现部分
//   ✓ 两者通过组合关联
//
// 行为要求 (运行时输出应展示):
//   ✓ 展示抽象操作委托给实现
//   ✓ 展示实现可以独立变化
//   ✓ 展示抽象和实现的独立扩展
//
// 输出要求:
//   ✓ 输出应包含模式名称: "=== {Pattern} Demo ==="
//   ✓ 输出至少 5 行非空内容
//   ✓ 输出不应包含 "TODO"
//
// 参考实现: .reference/{pattern_name}.cpp
// 评测命令: python3 scripts/evaluate.py build src
// ============================================

// TODO: 实现你的 Bridge

int main() {
    std::cout << "=== Bridge Demo ===\n";
    // TODO
}
