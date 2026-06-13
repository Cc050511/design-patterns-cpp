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

// ============================================
// 评测检查清单 (Evaluation Checklist)
// ============================================
// 完成本模式后，你的实现应该展示：
//
// 结构要求 (必须包含以下类/接口):
//   ✓ Subject 接口 (attach, detach, notify)
//   ✓ Observer 接口 (update)
//   ✓ ConcreteSubject 和 ConcreteObserver
//
// 行为要求 (运行时输出应展示):
//   ✓ 展示一对多依赖
//   ✓ 展示状态变化自动通知
//   ✓ 展示观察者注册/注销
//
// 输出要求:
//   ✓ 输出应包含模式名称: "=== {Pattern} Demo ==="
//   ✓ 输出至少 5 行非空内容
//   ✓ 输出不应包含 "TODO"
//
// 参考实现: .reference/{pattern_name}.cpp
// 评测命令: python3 scripts/evaluate.py build src
// ============================================

// TODO: 实现你的 Observer

int main() {
    std::cout << "=== Observer Demo ===\n";
    // TODO
}
