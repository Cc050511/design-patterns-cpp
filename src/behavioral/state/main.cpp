/**
 * State — 状态驱动的行为变化
 *
 * 核心结构：State接口 + 具体状态 + Context类 + 状态转换
 * 评测要点：
 *   - 结构：State类, Context类, 状态转换方法, virtual
 *   - 行为：展示状态变化、状态转换、不同行为
 *   - 输出：包含 "State", "state", "change", "behavior" 等关键词
 * 评测：python3 scripts/evaluate.py build src
 * 参考：.reference/state.cpp
 */

#include <memory>
#include <string>
#include <iostream>

// TODO: 实现此设计模式的所有类

int main() {
    std::cout << "=== State Demo ===\n";
    // TODO: 创建对象并演示设计模式
    std::cout << "State verified successfully.\n";
    return 0;
}
