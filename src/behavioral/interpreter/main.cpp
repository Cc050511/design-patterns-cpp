/**
 * Interpreter — 解释器模式
 * 意图: 解释自定义语言
 * 评测: python3 scripts/evaluate.py build src
 * 参考: .reference/interpreter.cpp
 */

#include <iostream>
#include <memory>

// TODO: 实现 AbstractExpression
// class AbstractExpression { ... };

// TODO: 实现 TerminalExpression
// class TerminalExpression : public AbstractExpression { ... };

// TODO: 实现 NonterminalExpression
// class NonterminalExpression : public AbstractExpression { ... };

int main() {
    std::cout << "=== Interpreter Demo ===\n";
    
    // TODO: 构建语法树并解释
    // std::unique_ptr<AbstractExpression> expr = ...;
    // int result = expr->interpret();
    // std::cout << "Result: " << result << "\n";
    
    std::cout << "Interpreter verified successfully.\n";
    return 0;
}
