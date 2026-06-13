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

#include <iostream>
#include <string>

// TODO: 实现你的 Adapter

int main() {
    std::cout << "=== Adapter Demo ===\n";
    // TODO
}
