/**
 * State — 状态模式
 * 意图: 状态驱动的行为变化
 * 评测: python3 scripts/evaluate.py build src
 * 参考: .reference/state.cpp
 */

#include <iostream>
#include <memory>

// TODO: 实现 State 接口
// class State { ... };

// TODO: 实现 ConcreteState
// class ConcreteState : public State { ... };

// TODO: 实现 Context 类
// class Context { ... };

int main() {
    std::cout << "=== State Demo ===\n";
    
    // TODO: 创建上下文，切换状态
    // Context context;
    // context.setState(std::make_unique<ConcreteState>());
    // context.request();
    
    std::cout << "State verified successfully.\n";
    return 0;
}
