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

#include <iostream>
#include <string>

// TODO: 实现你的 Facade

int main() {
    std::cout << "=== Facade Demo ===\n";
    // TODO
}
