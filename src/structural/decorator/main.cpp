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

// ============================================
// 评测检查清单 (Evaluation Checklist)
// ============================================
// 完成本模式后，你的实现应该展示：
//
// 结构要求 (必须包含以下类/接口):
//   ✓ Component 抽象基类
//   ✓ ConcreteComponent 基础对象
//   ✓ Decorator 抽象类 (继承 Component 且持有 Component*)
//
// 行为要求 (运行时输出应展示):
//   ✓ 展示装饰器添加职责
//   ✓ 展示装饰器可嵌套
//   ✓ 展示调用被装饰对象前后增强
//
// 输出要求:
//   ✓ 输出应包含模式名称: "=== {Pattern} Demo ==="
//   ✓ 输出至少 5 行非空内容
//   ✓ 输出不应包含 "TODO"
//
// 参考实现: .reference/{pattern_name}.cpp
// 评测命令: python3 scripts/evaluate.py build src
// ============================================

// TODO: 实现你的 Decorator

int main() {
    std::cout << "=== Decorator Demo ===\n";
    // TODO
}
