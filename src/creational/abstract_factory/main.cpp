/**
 * Abstract Factory — 创建一族相关对象
 * 意图: 创建一族相关对象
 * 评测: python3 scripts/evaluate.py build src
 * 参考: .reference/abstract_factory.cpp
 */

#include <memory>
#include <iostream>

// TODO: 完成以下类实现

class AbstractProductA {
public:
    virtual ~AbstractProductA() = default;
    virtual void useA() const = 0;
};

class AbstractProductB {
public:
    virtual ~AbstractProductB() = default;
    virtual void useB() const = 0;
};

class ConcreteProductA : public AbstractProductA {
public:
    void useA() const override {
        // TODO: Implement product A behavior
    }
};

class ConcreteProductB : public AbstractProductB {
public:
    void useB() const override {
        // TODO: Implement product B behavior
    }
};

class AbstractFactory {
public:
    virtual ~AbstractFactory() = default;
    virtual std::unique_ptr<AbstractProductA> createProductA() const = 0;
    virtual std::unique_ptr<AbstractProductB> createProductB() const = 0;
};

class ConcreteFactory : public AbstractFactory {
public:
    std::unique_ptr<AbstractProductA> createProductA() const override {
        return std::make_unique<ConcreteProductA>();
    }
    std::unique_ptr<AbstractProductB> createProductB() const override {
        return std::make_unique<ConcreteProductB>();
    }
};


int main() {
    std::cout << "=== Abstract Factory Demo ===\n";
    // TODO: Demonstrate Abstract Factory pattern
    std::cout << "Abstract Factory verified successfully.\n";
    return 0;
}
