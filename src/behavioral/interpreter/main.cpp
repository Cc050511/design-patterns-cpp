/**
 * Interpreter — 解释自定义语言
 * 意图: 解释自定义语言
 * 评测: python3 scripts/evaluate.py build src
 * 参考: .reference/interpreter.cpp
 */

#include <memory>
#include <string>
#include <iostream>

// TODO: 完成以下类实现

class Context {
public:
    explicit Context(const std::string& input) : input_(input) {}
    std::string getInput() const { return input_; }
    void setOutput(const std::string& output) { output_ = output; }
    std::string getOutput() const { return output_; }
private:
    std::string input_;
    std::string output_;
};

class Expression {
public:
    virtual ~Expression() = default;
    virtual void interpret(Context& context) const = 0;
};

class TerminalExpression : public Expression {
public:
    void interpret(Context& context) const override {
        // TODO: Interpret terminal expression
    }
};

class NonTerminalExpression : public Expression {
public:
    void interpret(Context& context) const override {
        // TODO: Interpret non-terminal expression (recursive)
    }
};

