/**
 * Template Method — 定义算法骨架，子类填充步骤
 * 意图: 定义算法骨架，子类填充步骤
 * 评测: python3 scripts/evaluate.py build src
 * 参考: .reference/template_method.cpp
 */

#include <iostream>

// TODO: 完成以下类实现

class AbstractClass {
public:
    virtual ~AbstractClass() = default;
    void templateMethod() const {
        // TODO: Define algorithm skeleton
        step1();
        step2();
        hook();
    }
protected:
    virtual void step1() const = 0;
    virtual void step2() const = 0;
    virtual void hook() const {
        // Optional hook with default behavior
    }
};

class ConcreteClass : public AbstractClass {
protected:
    void step1() const override {
        // TODO: Implement step 1
    }
    void step2() const override {
        // TODO: Implement step 2
    }
    void hook() const override {
        // TODO: Override hook (optional)
    }
};

