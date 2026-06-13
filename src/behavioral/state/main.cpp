/**
 * State — 状态驱动的行为变化
 * 意图: 状态驱动的行为变化
 * 评测: python3 scripts/evaluate.py build src
 * 参考: .reference/state.cpp
 */

#include <memory>
#include <string>
#include <iostream>

// TODO: 完成以下类实现

class Context;

class State {
public:
    virtual ~State() = default;
    virtual void handle(Context& context) = 0;
    virtual std::string getName() const = 0;
};

class Context {
public:
    explicit Context(std::unique_ptr<State> state) : state_(std::move(state)) {}
    void setState(std::unique_ptr<State> state) {
        state_ = std::move(state);
    }
    void request() {
        if (state_) state_->handle(*this);
    }
    std::string getStateName() const {
        return state_ ? state_->getName() : "none";
    }
private:
    std::unique_ptr<State> state_;
};

class ConcreteStateA : public State {
public:
    void handle(Context& context) override {
        // TODO: Handle in state A, possibly transition to state B
    }
    std::string getName() const override { return "StateA"; }
};

class ConcreteStateB : public State {
public:
    void handle(Context& context) override {
        // TODO: Handle in state B, possibly transition to state A
    }
    std::string getName() const override { return "StateB"; }
};

