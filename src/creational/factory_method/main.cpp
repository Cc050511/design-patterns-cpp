/**
 * Factory Method — 工厂方法模式
 * ==============================
 * 意图: 定义一个用于创建对象的接口，让子类决定实例化哪个类。
 *       工厂方法使一个类的实例化延迟到其子类。
 *
 * 练习要点:
 *   - Product 抽象基类 + ConcreteProduct
 *   - Creator 抽象基类，声明虚工厂方法 createProduct()
 *   - ConcreteCreator 重写工厂方法，返回具体的 Product
 *   - 客户端只依赖 Creator/Product 抽象接口
 *
 * 参考角色:
 *   Product (Button) ← ConcreteProduct (WinButton, MacButton)
 *   Creator (Dialog)  ← ConcreteCreator (WinDialog, MacDialog)
 */

#include <iostream>
#include <memory>

// TODO: 实现你的 Factory Method

int main() {
    std::cout << "=== Factory Method Demo ===\n";
    // TODO
}
