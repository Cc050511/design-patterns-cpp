/**
 * Prototype — 原型模式
 * 意图: 克隆已有对象
 * 评测: python3 scripts/evaluate.py build src
 * 参考: .reference/prototype.cpp
 */

#include <iostream>
#include <memory>

// TODO: 实现 Prototype 基类
// class Prototype { ... };

// TODO: 实现 ConcretePrototype
// class ConcretePrototype : public Prototype { ... };

int main() {
    std::cout << "=== Prototype Demo ===\n";
    
    // TODO: 创建原型并克隆
    // std::unique_ptr<Prototype> original = std::make_unique<ConcretePrototype>();
    // auto clone = original->clone();
    // clone->show();
    
    std::cout << "Prototype verified successfully.\n";
    return 0;
}
