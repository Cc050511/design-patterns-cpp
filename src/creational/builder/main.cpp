#include <iostream>
#include <string>

/**
 * Builder — 建造者模式
 * ======================
 * 意图: 将一个复杂对象的构建与它的表示分离，使得同样的构建过程可以创建不同的表示。
 *
 * 练习要点:
 *   - Builder 抽象接口定义构建步骤 (buildPartA, buildPartB, …)
 *   - ConcreteBuilder 实现步骤，并持有 Product
 *   - Director 定义构建顺序，接收 Builder&
 *   - 客户端选不同 Builder 注入 Director 得到不同 Product
 *
 * C++23 可选特性:
 *   - 显式对象参数 (this T&&) 实现完美转发构建链
 *   - std::optional 的 and_then / or_else / transform 链式处理可选步骤
 *   - std::print / std::println 替代 std::cout << 格式化输出
 *   - std::flat_map 管理默认配置项
 *
 * 参考角色:
 *   Builder (ResumeBuilder) ← ConcreteBuilder (PlainTextBuilder, HtmlBuilder)
 *   Director (ResumeDirector)
 *   Product (Resume)
 */

// ============================================
// 评测检查清单 (Evaluation Checklist)
// ============================================
// 完成本模式后，你的实现应该展示：
//
// 结构要求 (必须包含以下类/接口):
//   ✓ Builder 接口 (定义构建步骤)
//   ✓ ConcreteBuilder 实现步骤
//   ✓ Director 定义构建顺序
//   ✓ Product 最终产品
//
// 行为要求 (运行时输出应展示):
//   ✓ 展示分步骤构建
//   ✓ 展示 Director 协调构建
//   ✓ 展示不同 Builder 得到不同产品
//
// 输出要求:
//   ✓ 输出应包含模式名称: "=== {Pattern} Demo ==="
//   ✓ 输出至少 5 行非空内容
//   ✓ 输出不应包含 "TODO"
//
// 参考实现: .reference/{pattern_name}.cpp
// 评测命令: python3 scripts/evaluate.py build src
// ============================================

// TODO: 实现你的 Builder

int main() {
    std::cout << "=== Builder Demo ===\n";
    // TODO
}
