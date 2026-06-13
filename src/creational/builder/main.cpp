/**
 * Builder — 分步骤构建复杂对象
 * 意图: 分步骤构建复杂对象
 * 评测: python3 scripts/evaluate.py build src
 * 参考: .reference/builder.cpp
 */

#include <memory>
#include <string>
#include <iostream>

// TODO: 完成以下类实现

class Product {
public:
    void setPartA(const std::string& part) { partA_ = part; }
    void setPartB(const std::string& part) { partB_ = part; }
    void show() const {
        // TODO: Display product parts
    }
private:
    std::string partA_;
    std::string partB_;
};

class Builder {
public:
    virtual ~Builder() = default;
    virtual void buildPartA() = 0;
    virtual void buildPartB() = 0;
    virtual std::unique_ptr<Product> getResult() = 0;
};

class ConcreteBuilder : public Builder {
public:
    ConcreteBuilder() : product_(std::make_unique<Product>()) {}
    void buildPartA() override {
        // TODO: Build part A
    }
    void buildPartB() override {
        // TODO: Build part B
    }
    std::unique_ptr<Product> getResult() override {
        return std::move(product_);
    }
private:
    std::unique_ptr<Product> product_;
};

class Director {
public:
    explicit Director(Builder& builder) : builder_(builder) {}
    void construct() {
        // TODO: Define construction steps
        builder_.buildPartA();
        builder_.buildPartB();
    }
private:
    Builder& builder_;
};

