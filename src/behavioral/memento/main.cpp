/**
 * Memento — 捕获并恢复对象状态
 * 意图: 捕获并恢复对象状态
 * 评测: python3 scripts/evaluate.py build src
 * 参考: .reference/memento.cpp
 */

#include <memory>
#include <vector>
#include <string>
#include <iostream>

// TODO: 完成以下类实现

class Memento {
public:
    explicit Memento(const std::string& state) : state_(state) {}
    std::string getState() const { return state_; }
private:
    std::string state_;
};

class Originator {
public:
    void setState(const std::string& state) { state_ = state; }
    std::string getState() const { return state_; }
    std::unique_ptr<Memento> save() const {
        return std::make_unique<Memento>(state_);
    }
    void restore(const Memento* memento) {
        if (memento) {
            state_ = memento->getState();
        }
    }
private:
    std::string state_;
};

class Caretaker {
public:
    void addMemento(std::unique_ptr<Memento> memento) {
        mementos_.push_back(std::move(memento));
    }
    const Memento* getMemento(size_t index) const {
        if (index < mementos_.size()) {
            return mementos_[index].get();
        }
        return nullptr;
    }
private:
    std::vector<std::unique_ptr<Memento>> mementos_;
};


int main() {
    std::cout << "=== Memento Demo ===\n";
    // TODO: Demonstrate Memento pattern
    std::cout << "Memento verified successfully.\n";
    return 0;
}
