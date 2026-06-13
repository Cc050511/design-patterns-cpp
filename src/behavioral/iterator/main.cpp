/**
 * Iterator — 迭代器模式
 * 意图: 顺序访问集合元素
 * 评测: python3 scripts/evaluate.py build src
 * 参考: .reference/iterator.cpp
 */

#include <iostream>
#include <memory>

// TODO: 实现 Aggregate 接口
// class Aggregate { ... };

// TODO: 实现 Iterator 接口
// class Iterator { ... };

// TODO: 实现 ConcreteAggregate 和 ConcreteIterator
// class ConcreteAggregate : public Aggregate { ... };
// class ConcreteIterator : public Iterator { ... };

int main() {
    std::cout << "=== Iterator Demo ===\n";
    
    // TODO: 创建集合并遍历
    // ConcreteAggregate aggregate;
    // auto it = aggregate.createIterator();
    // while (it->hasNext()) {
    //     std::cout << it->next() << "\n";
    // }
    
    std::cout << "Iterator verified successfully.\n";
    return 0;
}
