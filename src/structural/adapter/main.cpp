/**
 * Adapter — 适配器模式
 * 意图: 转换接口以兼容
 * 评测: python3 scripts/evaluate.py build src
 * 参考: .reference/adapter.cpp
 */

#include <iostream>
#include <string>

// TODO: 实现 Target 接口
// class Target { ... };

// TODO: 实现 Adaptee 类
// class Adaptee { ... };

// TODO: 实现 Adapter 类
// class Adapter : public Target { ... };

int main() {
    std::cout << "=== Adapter Demo ===\n";
    
    // TODO: 使用 Adapter 调用不兼容接口
    // std::unique_ptr<Target> target = std::make_unique<Adapter>();
    // target->request();
    
    std::cout << "Adapter verified successfully.\n";
    return 0;
}
