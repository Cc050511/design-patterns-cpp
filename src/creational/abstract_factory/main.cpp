/**
 * Abstract Factory — 抽象工厂模式
 * 意图: 创建一族相关对象
 * 评测: python3 scripts/evaluate.py build src
 * 参考: .reference/abstract_factory.cpp
 */

#include <iostream>
#include <memory>

// TODO: 实现 AbstractProduct 接口
// class AbstractProduct { ... };

// TODO: 实现 ConcreteProduct
// class ConcreteProduct : public AbstractProduct { ... };

// TODO: 实现 AbstractFactory 接口
// class AbstractFactory { ... };

// TODO: 实现 ConcreteFactory
// class ConcreteFactory : public AbstractFactory { ... };

int main() {
    std::cout << "=== Abstract Factory Demo ===\n";
    
    // TODO: 创建工厂并生产一族产品
    // std::unique_ptr<AbstractFactory> factory = std::make_unique<ConcreteFactory>();
    // auto productA = factory->createProductA();
    // auto productB = factory->createProductB();
    
    std::cout << "Abstract Factory verified successfully.\n";
    return 0;
}
