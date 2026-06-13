/**
 * Observer — 一对多的依赖通知
 *
 * 核心结构：Subject接口 + Observer接口 + 具体主题 + 具体观察者
 * 评测要点：
 *   - 结构：Subject类, Observer类, attach/detach方法, notify方法
 *   - 行为：展示注册观察者、状态变化、通知更新、一对多通知
 *   - 输出：包含 "Observer", "attach", "state", "notify", "multiple" 等关键词
 * 评测：python3 scripts/evaluate.py build src
 * 参考：.reference/observer.cpp
 */

#include <memory>
#include <vector>
#include <string>
#include <iostream>

// TODO: 实现此设计模式的所有类

int main() {
    std::cout << "=== Observer Demo ===\n";
    // TODO: 创建对象并演示设计模式
    std::cout << "Observer verified successfully.\n";
    return 0;
}
