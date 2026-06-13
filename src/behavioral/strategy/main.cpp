/**
 * Strategy — 算法族，可互换
 * 意图: 算法族，可互换
 * 评测: python3 scripts/evaluate.py build src
 * 参考: .reference/strategy.cpp
 */

#include <memory>
#include <vector>
#include <string>
#include <iostream>

// TODO: 完成以下类实现

class Strategy {
public:
    virtual ~Strategy() = default;
    virtual void execute(const std::vector<int>& data) const = 0;
    virtual std::string getName() const = 0;
};

class ConcreteStrategyA : public Strategy {
public:
    void execute(const std::vector<int>& data) const override {
        // TODO: Implement algorithm A
    }
    std::string getName() const override { return "StrategyA"; }
};

class ConcreteStrategyB : public Strategy {
public:
    void execute(const std::vector<int>& data) const override {
        // TODO: Implement algorithm B
    }
    std::string getName() const override { return "StrategyB"; }
};

class Context {
public:
    explicit Context(std::unique_ptr<Strategy> strategy) : strategy_(std::move(strategy)) {}
    void setStrategy(std::unique_ptr<Strategy> strategy) {
        strategy_ = std::move(strategy);
    }
    void executeStrategy(const std::vector<int>& data) const {
        if (strategy_) {
            strategy_->execute(data);
        }
    }
    std::string getStrategyName() const {
        return strategy_ ? strategy_->getName() : "none";
    }
private:
    std::unique_ptr<Strategy> strategy_;
};

