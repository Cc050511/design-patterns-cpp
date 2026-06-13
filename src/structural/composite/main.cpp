/**
 * Composite — 树形结构的统一处理
 * 意图: 树形结构的统一处理
 * 评测: python3 scripts/evaluate.py build src
 * 参考: .reference/composite.cpp
 */

#include <memory>
#include <vector>
#include <iostream>

// TODO: 完成以下类实现

class Component {
public:
    virtual ~Component() = default;
    virtual void operation() const = 0;
    virtual void add(std::shared_ptr<Component> component) {}
    virtual void remove(std::shared_ptr<Component> component) {}
    virtual bool isComposite() const { return false; }
};

class Leaf : public Component {
public:
    void operation() const override {
        // TODO: Implement leaf operation
    }
};

class Composite : public Component {
public:
    void operation() const override {
        // TODO: Implement composite operation (iterate children)
        for (const auto& child : children_) {
            child->operation();
        }
    }
    void add(std::shared_ptr<Component> component) override {
        children_.push_back(component);
    }
    void remove(std::shared_ptr<Component> component) override {
        // TODO: Remove child
    }
    bool isComposite() const override { return true; }
private:
    std::vector<std::shared_ptr<Component>> children_;
};


int main() {
    std::cout << "=== Composite Demo ===\n";
    // TODO: Demonstrate Composite pattern
    std::cout << "Composite verified successfully.\n";
    return 0;
}
