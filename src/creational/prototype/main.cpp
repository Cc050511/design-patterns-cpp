/**
 * Prototype — 克隆已有对象
 * 意图: 克隆已有对象
 * 评测: python3 scripts/evaluate.py build src
 * 参考: .reference/prototype.cpp
 */

#include <memory>
#include <unordered_map>
#include <string>
#include <iostream>

// TODO: 完成以下类实现

class Prototype {
public:
    virtual ~Prototype() = default;
    virtual std::unique_ptr<Prototype> clone() const = 0;
    virtual void operation() const = 0;
};

class ConcretePrototype : public Prototype {
public:
    std::unique_ptr<Prototype> clone() const override {
        // TODO: Implement deep copy
        return std::make_unique<ConcretePrototype>(*this);
    }
    void operation() const override {
        // TODO: Implement operation
    }
};

class PrototypeManager {
public:
    void registerPrototype(const std::string& name, std::unique_ptr<Prototype> prototype) {
        // TODO: Register prototype
    }
    std::unique_ptr<Prototype> create(const std::string& name) {
        // TODO: Create from prototype
        return nullptr;
    }
private:
    std::unordered_map<std::string, std::unique_ptr<Prototype>> prototypes_;
};


int main() {
    std::cout << "=== Prototype Demo ===\n";
    // TODO: Demonstrate Prototype pattern
    std::cout << "Prototype verified successfully.\n";
    return 0;
}
