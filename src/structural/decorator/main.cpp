/**
 * Decorator — 动态添加职责
 * 意图: 动态添加职责
 * 评测: python3 scripts/evaluate.py build src
 * 参考: .reference/decorator.cpp
 */

#include <memory>
#include <iostream>

// TODO: 完成以下类实现

class Component {
public:
    virtual ~Component() = default;
    virtual void operation() const = 0;
};

class ConcreteComponent : public Component {
public:
    void operation() const override {
        // TODO: Implement base operation
    }
};

class Decorator : public Component {
public:
    explicit Decorator(std::unique_ptr<Component> component) 
        : component_(std::move(component)) {}
    void operation() const override {
        // TODO: Add behavior before/after delegating
        component_->operation();
    }
protected:
    std::unique_ptr<Component> component_;
};

class ConcreteDecorator : public Decorator {
public:
    using Decorator::Decorator;
    void operation() const override {
        // TODO: Add specific decoration
        Decorator::operation();
    }
};


int main() {
    std::cout << "=== Decorator Demo ===\n";
    // TODO: Demonstrate Decorator pattern
    std::cout << "Decorator verified successfully.\n";
    return 0;
}
