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

#include <iostream>
#include <memory>
#include <string>

// TODO: 实现你的 Interpreter

int main() {
    std::cout << "=== Interpreter Demo ===\n";
    // TODO
}
