/**
 * Template Method — 定义算法骨架，子类填充步骤
 *
 * 核心结构：AbstractClass + 模板方法 + 钩子方法 + 具体子类
 * 评测要点：
 *   - 结构：AbstractClass, 模板方法, 步骤/钩子方法, virtual
 *   - 行为：展示算法骨架、自定义步骤、不同实现
 *   - 输出：包含 "Template Method", "template", "step", "different" 等关键词
 * 评测：python3 scripts/evaluate.py build src
 * 参考：.reference/template_method.cpp
 */

#include <iostream>

// TODO: 实现此设计模式的所有类

int main() {
    std::cout << "=== Template Method Demo ===\n";
    // TODO: 创建对象并演示设计模式
    std::cout << "Template Method verified successfully.\n";
    return 0;
}
