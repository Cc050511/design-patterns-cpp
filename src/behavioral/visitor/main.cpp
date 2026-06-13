/**
 * Visitor — 访问者模式
 * ======================
 * 意图: 表示一个作用于某对象结构中的各元素的操作。
 *       它使你可以在不改变各元素的类的前提下定义作用于这些元素的新操作。
 *
 * 练习要点:
 *   - Visitor 接口: 为每种 ConcreteElement 声明一个 visit() 重载
 *   - ConcreteVisitor: 实现具体操作
 *   - Element 接口: 声明 accept(Visitor&)
 *   - ConcreteElement: 实现 accept() → visitor.visit(*this)  (双重分发!)
 *   - ObjectStructure: 管理元素集合，驱动遍历
 *
 * C++23 可选特性:
 *   - std::variant + std::visit 替代传统虚函数 Visitor (C++17 已可用)
 *   - std::expected 处理访问错误 (访问无效节点)
 *   - std::ranges::for_each 批量遍历元素集合
 *   - std::print / std::println 格式化输出访问日志
 *   - if constexpr 编译期分支替代部分运行时分发
 *
 * 参考角色:
 *   Visitor (IShapeVisitor) ← ConcreteVisitor (DrawVisitor, AreaVisitor)
 *   Element (Shape) ← ConcreteElement (Circle, Rectangle)
 *   ObjectStructure — 持有 vector<Shape*>
 */

#include <iostream>
#include <memory>
#include <vector>

// TODO: 实现你的 Visitor

int main() {
    std::cout << "=== Visitor Demo ===\n";
    // TODO
}
