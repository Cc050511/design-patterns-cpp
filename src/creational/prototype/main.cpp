/**
 * Prototype — 原型模式
 * ======================
 * 意图: 用原型实例指定创建对象的种类，并且通过拷贝这些原型创建新的对象。
 *
 * 练习要点:
 *   - 抽象基类声明 clone() 虚函数
 *   - 每个具体类用拷贝构造实现 clone()
 *   - Prototype Registry: 一个 map<string, Prototype*> 管理原型
 *   - 注意深拷贝 vs 浅拷贝
 *
 * C++23 可选特性:
 *   - std::clone_ptr (若编译器支持) 替代手写虚 clone
 *   - std::flat_map 替代 std::unordered_map 管理原型池
 *   - std::expected 处理 clone 失败
 *   - std::print / std::println 格式化输出
 *
 * 参考角色:
 *   Prototype (Shape) ← ConcretePrototype (Circle, Rectangle)
 *   PrototypeRegistry — 存储 & 查找原型
 */

#include <iostream>
#include <memory>
#include <string>

// TODO: 实现你的 Prototype

int main() {
    std::cout << "=== Prototype Demo ===\n";
    // TODO
}
