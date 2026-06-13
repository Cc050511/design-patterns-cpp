#include <iostream>
#include <memory>

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

// ============================================
// 评测检查清单 (Evaluation Checklist)
// ============================================
// 完成本模式后，你的实现应该展示：
//
// 结构要求 (必须包含以下类/接口):
//   ✓ Product 抽象基类
//   ✓ ConcreteProduct 子类
//   ✓ Creator 抽象基类 (含虚工厂方法)
//   ✓ ConcreteCreator 子类 (重写工厂方法)
//
// 行为要求 (运行时输出应展示):
//   ✓ 通过不同 Creator 创建不同 Product
//   ✓ 展示创建过程
//   ✓ 展示产品的使用
//
// 输出要求:
//   ✓ 输出应包含模式名称: "=== {Pattern} Demo ==="
//   ✓ 输出至少 5 行非空内容
//   ✓ 输出不应包含 "TODO"
//
// 参考实现: .reference/{pattern_name}.cpp
// 评测命令: python3 scripts/evaluate.py build src
// ============================================

// TODO: 实现你的 Factory Method

int main() {
    std::cout << "=== Factory Method Demo ===\n";
    // TODO
}
