/**
 * State — 状态模式
 * ==================
 * 意图: 允许一个对象在其内部状态改变时改变它的行为。
 *       对象看起来似乎修改了它的类。
 *
 * 练习要点:
 *   - State 接口: 声明各状态下的行为 (如 insertCoin, ejectCoin, turnCrank, dispense)
 *   - ConcreteState 每个子类实现一种状态下的行为
 *   - Context 持有当前 State*，委托所有行为给 State
 *   - 状态转换可以在 Context 或 State 中完成
 *
 * C++23 可选特性:
 *   - std::to_underlying 枚举状态转底层值 (便于日志和调试)
 *   - std::expected 状态转换错误处理 (无效转换可追踪)
 *   - if constexpr 编译期状态表 (简单状态机零开销)
 *   - std::print / std::println 格式化输出状态转移日志
 *   - std::unique_ptr<State> 管理状态生命周期
 *
 * 参考角色:
 *   Context (GumballMachine)
 *   State ← ConcreteState (NoCoinState, HasCoinState, SoldState, SoldOutState)
 *
 * 与 Strategy 的区别:
 *   - State: 状态由内部驱动，各状态之间互相知道，可自行转换
 *   - Strategy: 策略由外部注入，各策略之间互不相知
 */

#include <iostream>
#include <memory>
#include <string>

// TODO: 实现你的 State

int main() {
    std::cout << "=== State Demo ===\n";
    // TODO
}
