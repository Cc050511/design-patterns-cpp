#include <iostream>
#include <memory>
#include <string>

/**
 * Interpreter — 解释器模式
 * ==========================
 * 意图: 给定一个语言，定义它的文法的一种表示，并定义一个解释器，
 *       这个解释器使用该表示来解释语言中的句子。
 *
 * 练习要点:
 *   - AbstractExpression: 声明 interpret() 方法
 *   - TerminalExpression: 终结符 (如数字)
 *   - NonterminalExpression: 非终结符 (如运算符，包含子表达式)
 *   - Context: 可选的上下文信息
 *   - 构建语法树 (AST) 后递归 interpret
 *
 * 注意: 现代 C++ 中实际很少手写解释器，此练习重在理解递归组合结构。
 *
 * 参考角色:
 *   AbstractExpression (Expr) ← TerminalExpr (Number), NonTerminalExpr (Add, Sub, Mul)
 */

// ============================================
// 评测检查清单 (Evaluation Checklist)
// ============================================
// 完成本模式后，你的实现应该展示：
//
// 结构要求 (必须包含以下类/接口):
//   ✓ AbstractExpression (interpret 方法)
//   ✓ TerminalExpression 终结符
//   ✓ NonterminalExpression 非终结符
//
// 行为要求 (运行时输出应展示):
//   ✓ 展示语法解析
//   ✓ 展示表达式求值
//   ✓ 展示 AST 递归解释
//
// 输出要求:
//   ✓ 输出应包含模式名称: "=== {Pattern} Demo ==="
//   ✓ 输出至少 5 行非空内容
//   ✓ 输出不应包含 "TODO"
//
// 参考实现: .reference/{pattern_name}.cpp
// 评测命令: python3 scripts/evaluate.py build src
// ============================================

// TODO: 实现你的 Interpreter

int main() {
    std::cout << "=== Interpreter Demo ===\n";
    // TODO
}
