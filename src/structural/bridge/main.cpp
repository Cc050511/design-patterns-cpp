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

// TODO: 实现你的 Bridge

int main() {
    std::cout << "=== Bridge Demo ===\n";
    // TODO
}
