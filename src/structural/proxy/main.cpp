/**
 * Proxy — 控制对象访问
 * 意图: 控制对象访问
 * 评测: python3 scripts/evaluate.py build src
 * 参考: .reference/proxy.cpp
 */

#include <memory>
#include <iostream>

// TODO: 完成以下类实现

class Subject {
public:
    virtual ~Subject() = default;
    virtual void request() const = 0;
};

class RealSubject : public Subject {
public:
    void request() const override {
        // TODO: Implement real subject operation
    }
};

class Proxy : public Subject {
public:
    void request() const override {
        // TODO: Add access control, lazy initialization, logging, etc.
        if (!realSubject_) {
            realSubject_ = std::make_unique<RealSubject>();
        }
        realSubject_->request();
    }
private:
    mutable std::unique_ptr<RealSubject> realSubject_;
};


int main() {
    std::cout << "=== Proxy Demo ===\n";
    // TODO: Demonstrate Proxy pattern
    std::cout << "Proxy verified successfully.\n";
    return 0;
}
