/**
 * Strategy — 算法族，可互换
 *
 * 核心结构：Strategy接口 + 具体策略 + Context类 + 策略切换
 * 评测要点：
 *   - 结构：Strategy类, Context类, 算法方法, virtual
 *   - 行为：展示策略选择、策略切换、不同结果
 *   - 输出：包含 "Strategy", "strategy", "switch", "result" 等关键词
 * 评测：python3 scripts/evaluate.py build src
 * 参考：.reference/strategy.cpp
 */

#include <memory>
#include <vector>
#include <string>
#include <iostream>

// TODO: 实现此设计模式的所有类

int main() {
    std::cout << "=== Strategy Demo ===\n";
    // TODO: 创建对象并演示设计模式
    std::cout << "Strategy verified successfully.\n";
    return 0;
}
