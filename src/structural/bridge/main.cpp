/**
 * Bridge — 分离抽象与实现
 * 意图: 分离抽象与实现
 * 评测: python3 scripts/evaluate.py build src
 * 参考: .reference/bridge.cpp
 */

#include <memory>
#include <iostream>

// TODO: 完成以下类实现

class Implementor {
public:
    virtual ~Implementor() = default;
    virtual void operationImpl() const = 0;
};

class ConcreteImplementor : public Implementor {
public:
    void operationImpl() const override {
        // TODO: Implement platform-specific operation
    }
};

class Abstraction {
public:
    explicit Abstraction(std::unique_ptr<Implementor> impl) : impl_(std::move(impl)) {}
    virtual ~Abstraction() = default;
    virtual void operation() const {
        // TODO: Delegate to implementor
        impl_->operationImpl();
    }
protected:
    std::unique_ptr<Implementor> impl_;
};

class RefinedAbstraction : public Abstraction {
public:
    using Abstraction::Abstraction;
    void operation() const override {
        // TODO: Extended behavior
        Abstraction::operation();
    }
};


int main() {
    std::cout << "=== Bridge Demo ===\n";
    // TODO: Demonstrate Bridge pattern
    std::cout << "Bridge verified successfully.\n";
    return 0;
}
