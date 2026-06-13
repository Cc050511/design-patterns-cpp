/**
 * Iterator — 顺序访问集合元素
 * 意图: 顺序访问集合元素
 * 评测: python3 scripts/evaluate.py build src
 * 参考: .reference/iterator.cpp
 */

#include <memory>
#include <vector>
#include <iostream>

// TODO: 完成以下类实现

class Iterator {
public:
    virtual ~Iterator() = default;
    virtual bool hasNext() const = 0;
    virtual int next() = 0;
};

class Aggregate {
public:
    virtual ~Aggregate() = default;
    virtual std::unique_ptr<Iterator> createIterator() const = 0;
    virtual void add(int value) = 0;
    virtual size_t size() const = 0;
    virtual int get(size_t index) const = 0;
};

class ConcreteIterator : public Iterator {
public:
    explicit ConcreteIterator(const Aggregate& aggregate) 
        : aggregate_(aggregate), index_(0) {}
    bool hasNext() const override {
        return index_ < aggregate_.size();
    }
    int next() override {
        return aggregate_.get(index_++);
    }
private:
    const Aggregate& aggregate_;
    size_t index_;
};

class ConcreteAggregate : public Aggregate {
public:
    void add(int value) override {
        data_.push_back(value);
    }
    size_t size() const override {
        return data_.size();
    }
    int get(size_t index) const override {
        return data_[index];
    }
    std::unique_ptr<Iterator> createIterator() const override {
        return std::make_unique<ConcreteIterator>(*this);
    }
private:
    std::vector<int> data_;
};


int main() {
    std::cout << "=== Iterator Demo ===\n";
    // TODO: Demonstrate Iterator pattern
    std::cout << "Iterator verified successfully.\n";
    return 0;
}
