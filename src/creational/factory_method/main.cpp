/**
 * Factory Method — 子类决定创建哪个对象
 * 意图: 子类决定创建哪个对象
 * 评测: python3 scripts/evaluate.py build src
 * 参考: .reference/factory_method.cpp
 */

#include <memory>
#include <iostream>

// TODO: 完成以下类实现

class Product {
public:
    virtual ~Product() = default;
    virtual void use() const = 0;
};

class ConcreteProduct : public Product {
public:
    void use() const override {
        // TODO: Implement product behavior
    }
};

class Creator {
public:
    virtual ~Creator() = default;
    virtual std::unique_ptr<Product> createProduct() const = 0;
    void operation() const {
        // TODO: Implement operation using product
    }
};

class ConcreteCreator : public Creator {
public:
    std::unique_ptr<Product> createProduct() const override {
        // TODO: Return concrete product
        return std::make_unique<ConcreteProduct>();
    }
};

