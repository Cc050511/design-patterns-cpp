/**
 * Observer — 观察者模式
 * 意图: 一对多的依赖通知
 * 评测: python3 scripts/evaluate.py build src
 * 参考: .reference/observer.cpp
 */

#include <iostream>
#include <memory>
#include <vector>

// TODO: 实现 Subject 接口
// class Subject { ... };

// TODO: 实现 Observer 接口
// class Observer { ... };

// TODO: 实现 ConcreteSubject 和 ConcreteObserver
// class ConcreteSubject : public Subject { ... };
// class ConcreteObserver : public Observer { ... };

int main() {
    std::cout << "=== Observer Demo ===\n";
    
    // TODO: 创建主题和观察者，注册并通知
    // ConcreteSubject subject;
    // auto obs1 = std::make_unique<ConcreteObserver>();
    // subject.attach(obs1.get());
    // subject.setState("New State");
    // subject.notify();
    
    std::cout << "Observer verified successfully.\n";
    return 0;
}
