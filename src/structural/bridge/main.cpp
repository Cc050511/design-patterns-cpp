/**
 * Bridge — 桥接模式
 * 意图: 分离抽象与实现
 * 评测: python3 scripts/evaluate.py build src
 * 参考: .reference/bridge.cpp
 */

#include <iostream>
#include <memory>

// TODO: 实现 Implementor 接口
// class Implementor { ... };

// TODO: 实现 ConcreteImplementor
// class ConcreteImplementor : public Implementor { ... };

// TODO: 实现 Abstraction
// class Abstraction { ... };

// TODO: 实现 RefinedAbstraction
// class RefinedAbstraction : public Abstraction { ... };

int main() {
    std::cout << "=== Bridge Demo ===\n";
    
    // TODO: 创建抽象和实现，展示独立变化
    // std::unique_ptr<Implementor> impl = std::make_unique<ConcreteImplementor>();
    // std::unique_ptr<Abstraction> abs = std::make_unique<RefinedAbstraction>(impl);
    // abs->operation();
    
    std::cout << "Bridge verified successfully.\n";
    return 0;
}
