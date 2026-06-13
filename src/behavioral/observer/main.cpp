/**
 * Observer — 一对多的依赖通知
 * 意图: 一对多的依赖通知
 * 评测: python3 scripts/evaluate.py build src
 * 参考: .reference/observer.cpp
 */

#include <memory>
#include <vector>
#include <string>
#include <iostream>

// TODO: 完成以下类实现

class Observer {
public:
    virtual ~Observer() = default;
    virtual void update(const std::string& state) = 0;
};

class Subject {
public:
    virtual ~Subject() = default;
    void attach(std::shared_ptr<Observer> observer) {
        observers_.push_back(observer);
    }
    void detach(std::shared_ptr<Observer> observer) {
        // TODO: Remove observer
    }
    void notify(const std::string& state) {
        for (auto& observer : observers_) {
            observer->update(state);
        }
    }
    virtual void setState(const std::string& state) {
        state_ = state;
        notify(state);
    }
    std::string getState() const { return state_; }
protected:
    std::vector<std::shared_ptr<Observer>> observers_;
    std::string state_;
};

class ConcreteObserver : public Observer {
public:
    explicit ConcreteObserver(const std::string& name) : name_(name) {}
    void update(const std::string& state) override {
        // TODO: React to state change
    }
private:
    std::string name_;
};

class ConcreteSubject : public Subject {
public:
    void setState(const std::string& state) override {
        // TODO: Custom state logic
        Subject::setState(state);
    }
};

int main() {
    std::cout << "=== Observer Demo ===\n";
    ConcreteSubject subject;
    auto obs1 = std::make_shared<ConcreteObserver>("Observer1");
    auto obs2 = std::make_shared<ConcreteObserver>("Observer2");
    subject.attach(obs1);
    subject.attach(obs2);
    subject.setState("Active");
    subject.notify("Update");
    std::cout << "Observer verified successfully.\n";
    return 0;
}

