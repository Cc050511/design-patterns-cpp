/**
 * Factory Method — 工厂方法模式
 * 意图: 定义创建对象接口，让子类决定实例化哪个类
 * 评测: python3 scripts/evaluate.py build src
 * 参考: .reference/factory_method.cpp
 */

#include <iostream>
#include <memory>

// TODO: 实现 Product 接口
// class Product { ... };

// TODO: 实现 ConcreteProduct
// class ConcreteProduct : public Product { ... };

// TODO: 实现 Creator 抽象类
// class Creator { ... };

// TODO: 实现 ConcreteCreator
// class ConcreteCreator : public Creator { ... };

int main() {
    std::cout << "=== Factory Method Demo ===\n";
    
    // TODO: 创建不同工厂并生产产品
    // std::unique_ptr<Creator> creator = std::make_unique<ConcreteCreator>();
    // auto product = creator->createProduct();
    // product->use();
    
    std::cout << "Factory Method verified successfully.\n";
    return 0;
}
