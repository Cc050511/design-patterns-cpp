/**
 * Command — 将请求封装为对象
 * 意图: 将请求封装为对象
 * 评测: python3 scripts/evaluate.py build src
 * 参考: .reference/command.cpp
 */

#include <memory>
#include <iostream>

// TODO: 完成以下类实现

class Receiver {
public:
    void action() const {
        // TODO: Implement receiver action
    }
    void undo() const {
        // TODO: Implement undo action
    }
};

class Command {
public:
    virtual ~Command() = default;
    virtual void execute() const = 0;
    virtual void undo() const = 0;
};

class ConcreteCommand : public Command {
public:
    explicit ConcreteCommand(Receiver& receiver) : receiver_(receiver) {}
    void execute() const override {
        // TODO: Execute command
        receiver_.action();
    }
    void undo() const override {
        // TODO: Undo command
        receiver_.undo();
    }
private:
    Receiver& receiver_;
};

class Invoker {
public:
    void setCommand(std::unique_ptr<Command> command) {
        command_ = std::move(command);
    }
    void executeCommand() const {
        if (command_) command_->execute();
    }
    void undoCommand() const {
        if (command_) command_->undo();
    }
private:
    std::unique_ptr<Command> command_;
};


int main() {
    std::cout << "=== Command Demo ===\n";
    // TODO: Demonstrate Command pattern
    std::cout << "Command verified successfully.\n";
    return 0;
}
