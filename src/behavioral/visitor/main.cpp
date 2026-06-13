/**
 * Visitor — 访问者模式
 * 意图: 对一组对象执行新操作
 * 评测: python3 scripts/evaluate.py build src
 * 参考: .reference/visitor.cpp
 */

#include <iostream>
#include <memory>
#include <vector>

// TODO: 实现 Element 接口
// class Element { ... };

// TODO: 实现 ConcreteElement
// class ConcreteElement : public Element { ... };

// TODO: 实现 Visitor 接口
// class Visitor { ... };

// TODO: 实现 ConcreteVisitor
// class ConcreteVisitor : public Visitor { ... };

int main() {
    std::cout << "=== Visitor Demo ===\n";
    
    // TODO: 创建元素和访问者，执行访问
    // std::vector<std::unique_ptr<Element>> elements;
    // elements.push_back(std::make_unique<ConcreteElement>());
    // ConcreteVisitor visitor;
    // for (auto& elem : elements) {
    //     elem->accept(visitor);
    // }
    
    std::cout << "Visitor verified successfully.\n";
    return 0;
}
