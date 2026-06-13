#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>
#include <sstream>
#include <stdexcept>

// === Interpreter Demo ===
// Given a language, defines a representation for its grammar along with an interpreter.

// Abstract Expression
class Expression {
public:
    virtual ~Expression() = default;
    virtual int interpret(const std::unordered_map<std::string, int>& context) const = 0;
    virtual std::string toString() const = 0;
};

// Terminal Expression: Number
class Number : public Expression {
public:
    explicit Number(int value) : value_(value) {}

    int interpret(const std::unordered_map<std::string, int>&) const override {
        return value_;
    }

    std::string toString() const override {
        return std::to_string(value_);
    }

private:
    int value_;
};

// Terminal Expression: Variable
class Variable : public Expression {
public:
    explicit Variable(std::string name) : name_(std::move(name)) {}

    int interpret(const std::unordered_map<std::string, int>& context) const override {
        auto it = context.find(name_);
        if (it != context.end()) {
            return it->second;
        }
        throw std::runtime_error("Variable not found: " + name_);
    }

    std::string toString() const override {
        return name_;
    }

private:
    std::string name_;
};

// Non-terminal Expression: Addition
class Add : public Expression {
public:
    Add(std::unique_ptr<Expression> left, std::unique_ptr<Expression> right)
        : left_(std::move(left)), right_(std::move(right)) {}

    int interpret(const std::unordered_map<std::string, int>& context) const override {
        return left_->interpret(context) + right_->interpret(context);
    }

    std::string toString() const override {
        return "(" + left_->toString() + " + " + right_->toString() + ")";
    }

private:
    std::unique_ptr<Expression> left_;
    std::unique_ptr<Expression> right_;
};

// Non-terminal Expression: Subtraction
class Subtract : public Expression {
public:
    Subtract(std::unique_ptr<Expression> left, std::unique_ptr<Expression> right)
        : left_(std::move(left)), right_(std::move(right)) {}

    int interpret(const std::unordered_map<std::string, int>& context) const override {
        return left_->interpret(context) - right_->interpret(context);
    }

    std::string toString() const override {
        return "(" + left_->toString() + " - " + right_->toString() + ")";
    }

private:
    std::unique_ptr<Expression> left_;
    std::unique_ptr<Expression> right_;
};

// Non-terminal Expression: Multiplication
class Multiply : public Expression {
public:
    Multiply(std::unique_ptr<Expression> left, std::unique_ptr<Expression> right)
        : left_(std::move(left)), right_(std::move(right)) {}

    int interpret(const std::unordered_map<std::string, int>& context) const override {
        return left_->interpret(context) * right_->interpret(context);
    }

    std::string toString() const override {
        return "(" + left_->toString() + " * " + right_->toString() + ")";
    }

private:
    std::unique_ptr<Expression> left_;
    std::unique_ptr<Expression> right_;
};

// Simple parser to build expression tree from tokens
class ExpressionParser {
public:
    static std::unique_ptr<Expression> parse(const std::string& input) {
        std::vector<std::string> tokens = tokenize(input);
        size_t pos = 0;
        return parseExpression(tokens, pos);
    }

private:
    static std::vector<std::string> tokenize(const std::string& input) {
        std::vector<std::string> tokens;
        std::stringstream ss(input);
        std::string token;
        while (ss >> token) {
            tokens.push_back(token);
        }
        return tokens;
    }

    static std::unique_ptr<Expression> parseExpression(const std::vector<std::string>& tokens, size_t& pos) {
        if (pos >= tokens.size()) {
            return std::make_unique<Number>(0);
        }

        auto left = parseTerm(tokens, pos);

        while (pos < tokens.size() && (tokens[pos] == "+" || tokens[pos] == "-")) {
            std::string op = tokens[pos++];
            auto right = parseTerm(tokens, pos);
            if (op == "+") {
                left = std::make_unique<Add>(std::move(left), std::move(right));
            } else {
                left = std::make_unique<Subtract>(std::move(left), std::move(right));
            }
        }

        return left;
    }

    static std::unique_ptr<Expression> parseTerm(const std::vector<std::string>& tokens, size_t& pos) {
        auto left = parseFactor(tokens, pos);

        while (pos < tokens.size() && tokens[pos] == "*") {
            pos++;
            auto right = parseFactor(tokens, pos);
            left = std::make_unique<Multiply>(std::move(left), std::move(right));
        }

        return left;
    }

    static std::unique_ptr<Expression> parseFactor(const std::vector<std::string>& tokens, size_t& pos) {
        if (pos >= tokens.size()) {
            return std::make_unique<Number>(0);
        }

        std::string token = tokens[pos++];

        if (token == "(") {
            auto expr = parseExpression(tokens, pos);
            if (pos < tokens.size() && tokens[pos] == ")") {
                pos++;
            }
            return expr;
        }

        // Check if it's a number
        try {
            size_t idx;
            int value = std::stoi(token, &idx);
            if (idx == token.size()) {
                return std::make_unique<Number>(value);
            }
        } catch (...) {}

        // Otherwise it's a variable
        return std::make_unique<Variable>(token);
    }
};

int main() {
    std::cout << "=== Interpreter Demo ===" << std::endl;

    // Context with variable values
    std::unordered_map<std::string, int> context = {
        {"x", 10},
        {"y", 5},
        {"z", 2}
    };

    // Test 1: Simple expression
    std::cout << "--- Manual Expression Tree ---" << std::endl;
    auto expr1 = std::make_unique<Add>(
        std::make_unique<Number>(10),
        std::make_unique<Number>(5)
    );
    std::cout << "Expression: " << expr1->toString() << std::endl;
    std::cout << "Result: " << expr1->interpret(context) << std::endl;
    std::cout << std::endl;

    // Test 2: Expression with variables
    auto expr2 = std::make_unique<Multiply>(
        std::make_unique<Variable>("x"),
        std::make_unique<Add>(
            std::make_unique<Variable>("y"),
            std::make_unique<Variable>("z")
        )
    );
    std::cout << "Expression: " << expr2->toString() << std::endl;
    std::cout << "Result: " << expr2->interpret(context) << std::endl;
    std::cout << std::endl;

    // Test 3: Parsed expression
    std::cout << "--- Parsed Expression ---" << std::endl;
    auto parsed = ExpressionParser::parse("x + y * z");
    std::cout << "Parsed: " << parsed->toString() << std::endl;
    std::cout << "Result: " << parsed->interpret(context) << std::endl;
    std::cout << std::endl;

    auto parsed2 = ExpressionParser::parse("10 + 5 - 3");
    std::cout << "Parsed: " << parsed2->toString() << std::endl;
    std::cout << "Result: " << parsed2->interpret(context) << std::endl;

    std::cout << std::endl;
    std::cout << "Interpreter pattern defines grammar and interprets sentences" << std::endl;
    std::cout << "=== End Interpreter Demo ===" << std::endl;
    return 0;
}
