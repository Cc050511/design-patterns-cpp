/**
 * Observer — 观察者模式
 * ========================
 * 意图: 定义对象间的一种一对多的依赖关系，当一个对象的状态发生改变时，
 *       所有依赖于它的对象都得到通知并被自动更新。
 *
 * 练习要点:
 *   - Subject 接口: attach(), detach(), notify()
 *   - Observer 接口: update()
 *   - ConcreteSubject (如 WeatherData) — 持有状态，状态变化时调用 notify()
 *   - ConcreteObserver (如 Display) — 在 update() 中拉取所需数据
 *   - 可考虑 Push vs Pull 两种数据传递方式
 *
 * C++23 可选特性:
 *   - std::move_only_function 替代 std::function 绑定只移 lambda 回调
 *   - std::ranges::for_each 遍历通知所有观察者
 *   - std::weak_ptr 解决生命周期问题 (Observer 自动 detach)
 *   - std::print / std::println 格式化输出通知日志
 *
 * 参考角色:
 *   Subject (WeatherData) ← ConcreteSubject
 *   Observer (Display)    ← ConcreteObserver (CurrentConditions, Statistics, Alert)
 */

#include <iostream>
#include <memory>
#include <vector>

// TODO: 实现你的 Observer

int main() {
    std::cout << "=== Observer Demo ===\n";
    // TODO
}
