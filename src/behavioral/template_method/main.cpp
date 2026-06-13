/**
 * Template Method — 模板方法模式
 * ================================
 * 意图: 定义一个操作中的算法的骨架，而将一些步骤延迟到子类中。
 *       模板方法使得子类可以不改变一个算法的结构即可重定义该算法的某些特定步骤。
 *
 * 练习要点:
 *   - 基类定义模板方法 (非虚函数，描述算法步骤) 和钩子操作 (虚函数)
 *   - 钩子操作: 可以是纯虚的 (must override) 或带默认实现 (may override)
 *   - 子类只重写钩子操作，不改变模板方法
 *   - 好莱坞原则: "Don't call us, we'll call you."
 *
 * C++23 可选特性:
 *   - if constexpr 编译期钩子替代部分虚函数
 *   - 显式对象参数 (this T&&) 实现完美转发步骤
 *   - std::expected 错误处理 (步骤返回 expected<void, Error>)
 *   - std::print / std::println 格式化输出步骤日志
 *   - NVI 惯用法: public 非虚模板方法调用 private virtual 步骤
 *
 * 参考角色:
 *   AbstractClass (DataMiner) ← ConcreteClass (CSVMiner, JSONMiner)
 *   模板方法是基类中的一个非虚 public 方法，内部按序调用 private virtual 步骤
 *
 * 与 Strategy 的区别:
 *   - Template Method: 用继承，在编译期确定算法骨架
 *   - Strategy: 用组合，在运行期切换整个算法
 */

#include <iostream>
#include <string>

// TODO: 实现你的 Template Method

int main() {
    std::cout << "=== Template Method Demo ===\n";
    // TODO
}
