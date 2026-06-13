/**
 * Abstract Factory — 抽象工厂模式
 * =================================
 * 意图: 提供一个创建一系列相关或相互依赖对象的接口，而无需指定它们的具体类。
 *
 * 练习要点:
 *   - 多条产品线 (如 Button + Checkbox)，每条有多个变体 (Win/Mac)
 *   - AbstractFactory 接口声明创建每种产品的方法
 *   - ConcreteFactory (WinFactory, MacFactory) 创建同族产品
 *   - 与 Factory Method 的区别: 抽象工厂创建"一族"产品，工厂方法创建"一个"产品
 *
 * 参考角色:
 *   AbstractFactory (GUIFactory)  ← ConcreteFactory (WinFactory, MacFactory)
 *   AbstractProduct (Button, Checkbox) ← ConcreteProduct (WinButton, MacCheckbox…)
 */

#include <iostream>
#include <memory>

// TODO: 实现你的 Abstract Factory

int main() {
    std::cout << "=== Abstract Factory Demo ===\n";
    // TODO
}
