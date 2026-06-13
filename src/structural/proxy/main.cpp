/**
 * Proxy — 控制对象访问
 *
 * 核心结构：Subject接口 + RealSubject + Proxy（控制访问）
 * 评测要点：
 *   - 结构：Proxy类, RealSubject类, Subject接口, 访问控制
 *   - 行为：展示代理控制、真实对象、延迟创建
 *   - 输出：包含 "Proxy", "proxy", "real", "lazy" 等关键词
 * 评测：python3 scripts/evaluate.py build src
 * 参考：.reference/proxy.cpp
 */

#include <memory>
#include <iostream>

// TODO: 实现此设计模式的所有类

int main() {
    std::cout << "=== Proxy Demo ===\n";
    // TODO: 创建对象并演示设计模式
    std::cout << "Proxy verified successfully.\n";
    return 0;
}
