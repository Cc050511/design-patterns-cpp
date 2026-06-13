/**
 * Visitor — 对一组对象执行新操作
 * 意图: 对一组对象执行新操作
 * 评测: python3 scripts/evaluate.py build src
 * 参考: .reference/visitor.cpp
 */

#include <memory>
#include <string>
#include <iostream>

// TODO: 完成以下类实现

class Element;

class Visitor {
public:
    virtual ~Visitor() = default;
    virtual void visitConcreteElementA(const Element& element) = 0;
    virtual void visitConcreteElementB(const Element& element) = 0;
};

class Element {
public:
    virtual ~Element() = default;
    virtual void accept(Visitor& visitor) const = 0;
    virtual std::string getName() const = 0;
};

class ConcreteElementA : public Element {
public:
    void accept(Visitor& visitor) const override {
        visitor.visitConcreteElementA(*this);
    }
    std::string getName() const override { return "ElementA"; }
};

class ConcreteElementB : public Element {
public:
    void accept(Visitor& visitor) const override {
        visitor.visitConcreteElementB(*this);
    }
    std::string getName() const override { return "ElementB"; }
};

class ConcreteVisitor : public Visitor {
public:
    void visitConcreteElementA(const Element& element) override {
        // TODO: Visit element A
    }
    void visitConcreteElementB(const Element& element) override {
        // TODO: Visit element B
    }
private:
    std::string result_;
};

