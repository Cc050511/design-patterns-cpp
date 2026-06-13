/**
 * Singleton — 单例模式
 * 意图: 全局唯一实例，禁止拷贝，延迟初始化
 * 评测: python3 scripts/evaluate.py build src
 * 参考: .reference/singleton.cpp
 */

#include <iostream>

// TODO: 实现 Singleton 类
// 要求:
//   - 禁止外部构造（private 构造函数）
//   - 提供 instance() 静态方法（返回唯一实例）
//   - 禁止拷贝/移动（= delete 或 private）
// class Singleton {
//     ...
// };

int main() {
    std::cout << "=== Singleton Demo ===\n";
    std::cout << "Getting instance 1...\n";
    
    // TODO: 获取实例并调用方法
    // Singleton& s1 = Singleton::instance();
    // s1.operation();
    
    std::cout << "Getting instance 2...\n";
    
    // TODO: 再次获取实例
    // Singleton& s2 = Singleton::instance();
    // s2.operation();
    
    // TODO: 验证是同一实例
    // std::cout << "Same instance? " << (&s1 == &s2 ? "YES" : "NO") << "\n";
    
    std::cout << "Singleton verified successfully.\n";
    return 0;
}
