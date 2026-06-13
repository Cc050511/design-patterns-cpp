/**
 * Decorator — 装饰器模式
 * ========================
 * 意图: 动态地给一个对象添加一些额外的职责。
 *       就增加功能来说，Decorator 模式比生成子类更为灵活。
 *
 * 练习要点:
 *   - Component 抽象基类 (定义被装饰对象的接口)
 *   - ConcreteComponent (基础对象)
 *   - Decorator 抽象类: 继承 Component 且持有 Component* (关键!)
 *   - ConcreteDecorator: 在调用被装饰对象前后添加行为
 *   - 装饰器可嵌套: new DecoratorB(new DecoratorA(new Component()))
 *
 * C++23 可选特性:
 *   - 显式对象参数 (this T&&) 实现完美转发，省 4 份重载
 *   - std::move_only_function 绑定只移 lambda 装饰器
 *   - std::print / std::println 格式化输出装饰日志
 *   - std::unique_ptr<Component> 持有被装饰对象
 *
 * 参考角色:
 *   Component (Beverage) ← ConcreteComponent (Espresso), Decorator (CondimentDecorator)
 *   ConcreteDecorator (Milk, Mocha, Whip)
 */

#include <iostream>
#include <memory>
#include <string>

// TODO: 实现你的 Decorator

int main() {
    std::cout << "=== Decorator Demo ===\n";
    // TODO
}
