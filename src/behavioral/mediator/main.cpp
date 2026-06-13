/**
 * Mediator — 集中协调对象交互
 * 意图: 集中协调对象交互
 * 评测: python3 scripts/evaluate.py build src
 * 参考: .reference/mediator.cpp
 */

#include <memory>
#include <vector>
#include <string>
#include <iostream>

// TODO: 完成以下类实现

class Colleague;

class Mediator {
public:
    virtual ~Mediator() = default;
    virtual void notify(Colleague* sender, const std::string& event) = 0;
};

class Colleague {
public:
    explicit Colleague(Mediator* mediator) : mediator_(mediator) {}
    virtual ~Colleague() = default;
    void send(const std::string& event) {
        if (mediator_) mediator_->notify(this, event);
    }
    virtual void receive(const std::string& event) = 0;
protected:
    Mediator* mediator_;
};

class ConcreteMediator : public Mediator {
public:
    void addColleague(Colleague* colleague) {
        colleagues_.push_back(colleague);
    }
    void notify(Colleague* sender, const std::string& event) override {
        // TODO: Coordinate communication between colleagues
        for (auto* colleague : colleagues_) {
            if (colleague != sender) {
                colleague->receive(event);
            }
        }
    }
private:
    std::vector<Colleague*> colleagues_;
};

class ConcreteColleague : public Colleague {
public:
    using Colleague::Colleague;
    void receive(const std::string& event) override {
        // TODO: Handle received event
    }
};


int main() {
    std::cout << "=== Mediator Demo ===\n";
    // TODO: Demonstrate Mediator pattern
    std::cout << "Mediator verified successfully.\n";
    return 0;
}
