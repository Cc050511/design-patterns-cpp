#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <stack>

// === Command Demo ===
// Encapsulates a request as an object, thereby letting you parameterize clients with different requests.

// Command interface
class Command {
public:
    virtual ~Command() = default;
    virtual void execute() = 0;
    virtual void undo() = 0;
    virtual std::string getDescription() const = 0;
};

// Receiver: Light
class Light {
public:
    void on() {
        isOn_ = true;
        std::cout << "Light is ON" << std::endl;
    }
    void off() {
        isOn_ = false;
        std::cout << "Light is OFF" << std::endl;
    }
    bool isOn() const { return isOn_; }
private:
    bool isOn_ = false;
};

// Receiver: Fan
class Fan {
public:
    void high() {
        speed_ = 3;
        std::cout << "Fan is on HIGH" << std::endl;
    }
    void medium() {
        speed_ = 2;
        std::cout << "Fan is on MEDIUM" << std::endl;
    }
    void low() {
        speed_ = 1;
        std::cout << "Fan is on LOW" << std::endl;
    }
    void off() {
        prevSpeed_ = speed_;
        speed_ = 0;
        std::cout << "Fan is OFF" << std::endl;
    }
    int getSpeed() const { return speed_; }
    int getPreviousSpeed() const { return prevSpeed_; }
private:
    int speed_ = 0;
    int prevSpeed_ = 0;
};

// Concrete Command: LightOn
class LightOnCommand : public Command {
public:
    explicit LightOnCommand(std::shared_ptr<Light> light) : light_(light) {}

    void execute() override {
        light_->on();
    }

    void undo() override {
        light_->off();
    }

    std::string getDescription() const override { return "Light ON"; }

private:
    std::shared_ptr<Light> light_;
};

// Concrete Command: LightOff
class LightOffCommand : public Command {
public:
    explicit LightOffCommand(std::shared_ptr<Light> light) : light_(light) {}

    void execute() override {
        light_->off();
    }

    void undo() override {
        light_->on();
    }

    std::string getDescription() const override { return "Light OFF"; }

private:
    std::shared_ptr<Light> light_;
};

// Concrete Command: FanHigh
class FanHighCommand : public Command {
public:
    explicit FanHighCommand(std::shared_ptr<Fan> fan) : fan_(fan), prevSpeed_(0) {}

    void execute() override {
        prevSpeed_ = fan_->getSpeed();
        fan_->high();
    }

    void undo() override {
        if (prevSpeed_ == 0) {
            fan_->off();
        } else if (prevSpeed_ == 1) {
            fan_->low();
        } else if (prevSpeed_ == 2) {
            fan_->medium();
        } else {
            fan_->high();
        }
    }

    std::string getDescription() const override { return "Fan HIGH"; }

private:
    std::shared_ptr<Fan> fan_;
    int prevSpeed_;
};

// Invoker: Remote Control
class RemoteControl {
public:
    void setCommand(std::unique_ptr<Command> command) {
        command_ = std::move(command);
    }

    void pressButton() {
        if (command_) {
            command_->execute();
            history_.push(command_.get());
        }
    }

    void pressUndo() {
        if (!history_.empty()) {
            Command* cmd = history_.top();
            std::cout << "Undoing: " << cmd->getDescription() << std::endl;
            cmd->undo();
            history_.pop();
        } else {
            std::cout << "Nothing to undo" << std::endl;
        }
    }

private:
    std::unique_ptr<Command> command_;
    std::stack<Command*> history_;
};

// Macro Command (composite command)
class MacroCommand : public Command {
public:
    void addCommand(std::unique_ptr<Command> cmd) {
        commands_.push_back(std::move(cmd));
    }

    void execute() override {
        std::cout << "Executing macro command:" << std::endl;
        for (auto& cmd : commands_) {
            cmd->execute();
        }
    }

    void undo() override {
        std::cout << "Undoing macro command:" << std::endl;
        for (auto it = commands_.rbegin(); it != commands_.rend(); ++it) {
            (*it)->undo();
        }
    }

    std::string getDescription() const override { return "Macro Command"; }

private:
    std::vector<std::unique_ptr<Command>> commands_;
};

int main() {
    std::cout << "=== Command Demo ===" << std::endl;

    auto livingRoomLight = std::make_shared<Light>();
    auto ceilingFan = std::make_shared<Fan>();

    RemoteControl remote;

    std::cout << "--- Single Commands ---" << std::endl;
    remote.setCommand(std::make_unique<LightOnCommand>(livingRoomLight));
    remote.pressButton();
    remote.pressUndo();
    std::cout << std::endl;

    remote.setCommand(std::make_unique<FanHighCommand>(ceilingFan));
    remote.pressButton();
    remote.pressUndo();
    std::cout << std::endl;

    std::cout << "--- Macro Command ---" << std::endl;
    auto partyMode = std::make_unique<MacroCommand>();
    partyMode->addCommand(std::make_unique<LightOnCommand>(livingRoomLight));
    partyMode->addCommand(std::make_unique<FanHighCommand>(ceilingFan));

    remote.setCommand(std::move(partyMode));
    remote.pressButton();
    std::cout << std::endl;
    remote.pressUndo();

    std::cout << std::endl;
    std::cout << "Command pattern encapsulates requests as objects" << std::endl;
    std::cout << "=== End Command Demo ===" << std::endl;
    return 0;
}
