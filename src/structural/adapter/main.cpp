/**
 * Adapter — 转换接口以兼容
 * 意图: 转换接口以兼容
 * 评测: python3 scripts/evaluate.py build src
 * 参考: .reference/adapter.cpp
 */

#include <memory>
#include <iostream>

// TODO: 完成以下类实现

class Target {
public:
    virtual ~Target() = default;
    virtual void request() const = 0;
};

class Adaptee {
public:
    void specificRequest() const {
        // TODO: Implement specific request
    }
};

class Adapter : public Target {
public:
    void request() const override {
        // TODO: Adapt Adaptee's interface to Target
        adaptee_.specificRequest();
    }
private:
    Adaptee adaptee_;
};

