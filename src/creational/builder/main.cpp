/**
 * Builder — 分步骤构建复杂对象
 *
 * 核心结构：Product类 + Builder接口 + Director类 + 具体Builder
 * 评测要点：
 *   - 结构：Builder类, Director类, buildPart*方法, 链式调用
 *   - 行为：展示构建步骤、Director协调、不同产品配置
 *   - 输出：包含 "Builder", "build", "step", "Director", "different" 等关键词
 * 评测：python3 scripts/evaluate.py build src
 * 参考：.reference/builder.cpp
 */

#include <memory>
#include <string>
#include <iostream>

// TODO: 实现此设计模式的所有类

int main() {
    std::cout << "=== Builder Demo ===\n";
    // TODO: 创建对象并演示设计模式
    std::cout << "Builder verified successfully.\n";
    return 0;
}
