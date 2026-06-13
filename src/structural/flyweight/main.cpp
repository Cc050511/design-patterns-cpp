/**
 * Flyweight — 共享细粒度对象
 * 意图: 共享细粒度对象
 * 评测: python3 scripts/evaluate.py build src
 * 参考: .reference/flyweight.cpp
 */

#include <memory>
#include <unordered_map>
#include <string>
#include <iostream>

// TODO: 完成以下类实现

class Flyweight {
public:
    virtual ~Flyweight() = default;
    virtual void operation(const std::string& extrinsicState) const = 0;
};

class ConcreteFlyweight : public Flyweight {
public:
    explicit ConcreteFlyweight(const std::string& intrinsicState) 
        : intrinsicState_(intrinsicState) {}
    void operation(const std::string& extrinsicState) const override {
        // TODO: Use intrinsic and extrinsic state
    }
private:
    std::string intrinsicState_;
};

class FlyweightFactory {
public:
    std::shared_ptr<Flyweight> getFlyweight(const std::string& key) {
        // TODO: Return existing or create new flyweight
        auto it = flyweights_.find(key);
        if (it == flyweights_.end()) {
            auto fw = std::make_shared<ConcreteFlyweight>(key);
            flyweights_[key] = fw;
            return fw;
        }
        return it->second;
    }
private:
    std::unordered_map<std::string, std::shared_ptr<Flyweight>> flyweights_;
};

