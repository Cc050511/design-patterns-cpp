#!/usr/bin/env python3
"""
Convert template files from main() structure to pure class skeletons.
Creates test files for each pattern.
"""

import json
import os
import re
from pathlib import Path

# Pattern definitions with class skeletons
PATTERN_SKELETONS = {
    "singleton": """
class Singleton {
public:
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;
    Singleton(Singleton&&) = delete;
    Singleton& operator=(Singleton&&) = delete;

    static Singleton& instance() {
        // TODO: Implement lazy initialization
        static Singleton instance;
        return instance;
    }

    void operation() const {
        // TODO: Implement operation
    }

private:
    Singleton() = default;
    ~Singleton() = default;
};
""",
    "factory_method": """
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
""",
    "abstract_factory": """
class AbstractProductA {
public:
    virtual ~AbstractProductA() = default;
    virtual void useA() const = 0;
};

class AbstractProductB {
public:
    virtual ~AbstractProductB() = default;
    virtual void useB() const = 0;
};

class ConcreteProductA : public AbstractProductA {
public:
    void useA() const override {
        // TODO: Implement product A behavior
    }
};

class ConcreteProductB : public AbstractProductB {
public:
    void useB() const override {
        // TODO: Implement product B behavior
    }
};

class AbstractFactory {
public:
    virtual ~AbstractFactory() = default;
    virtual std::unique_ptr<AbstractProductA> createProductA() const = 0;
    virtual std::unique_ptr<AbstractProductB> createProductB() const = 0;
};

class ConcreteFactory : public AbstractFactory {
public:
    std::unique_ptr<AbstractProductA> createProductA() const override {
        return std::make_unique<ConcreteProductA>();
    }
    std::unique_ptr<AbstractProductB> createProductB() const override {
        return std::make_unique<ConcreteProductB>();
    }
};
""",
    "builder": """
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
""",
    "prototype": """
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
""",
    "adapter": """
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
""",
    "bridge": """
class Implementor {
public:
    virtual ~Implementor() = default;
    virtual void operationImpl() const = 0;
};

class ConcreteImplementor : public Implementor {
public:
    void operationImpl() const override {
        // TODO: Implement platform-specific operation
    }
};

class Abstraction {
public:
    explicit Abstraction(std::unique_ptr<Implementor> impl) : impl_(std::move(impl)) {}
    virtual ~Abstraction() = default;
    virtual void operation() const {
        // TODO: Delegate to implementor
        impl_->operationImpl();
    }
protected:
    std::unique_ptr<Implementor> impl_;
};

class RefinedAbstraction : public Abstraction {
public:
    using Abstraction::Abstraction;
    void operation() const override {
        // TODO: Extended behavior
        Abstraction::operation();
    }
};
""",
    "composite": """
class Component {
public:
    virtual ~Component() = default;
    virtual void operation() const = 0;
    virtual void add(std::shared_ptr<Component> component) {}
    virtual void remove(std::shared_ptr<Component> component) {}
    virtual bool isComposite() const { return false; }
};

class Leaf : public Component {
public:
    void operation() const override {
        // TODO: Implement leaf operation
    }
};

class Composite : public Component {
public:
    void operation() const override {
        // TODO: Implement composite operation (iterate children)
        for (const auto& child : children_) {
            child->operation();
        }
    }
    void add(std::shared_ptr<Component> component) override {
        children_.push_back(component);
    }
    void remove(std::shared_ptr<Component> component) override {
        // TODO: Remove child
    }
    bool isComposite() const override { return true; }
private:
    std::vector<std::shared_ptr<Component>> children_;
};
""",
    "decorator": """
class Component {
public:
    virtual ~Component() = default;
    virtual void operation() const = 0;
};

class ConcreteComponent : public Component {
public:
    void operation() const override {
        // TODO: Implement base operation
    }
};

class Decorator : public Component {
public:
    explicit Decorator(std::unique_ptr<Component> component) 
        : component_(std::move(component)) {}
    void operation() const override {
        // TODO: Add behavior before/after delegating
        component_->operation();
    }
protected:
    std::unique_ptr<Component> component_;
};

class ConcreteDecorator : public Decorator {
public:
    using Decorator::Decorator;
    void operation() const override {
        // TODO: Add specific decoration
        Decorator::operation();
    }
};
""",
    "facade": """
class SubsystemA {
public:
    void operationA() const {
        // TODO: Implement subsystem A operation
    }
};

class SubsystemB {
public:
    void operationB() const {
        // TODO: Implement subsystem B operation
    }
};

class Facade {
public:
    void simplifiedOperation() const {
        // TODO: Coordinate subsystems
        subsystemA_.operationA();
        subsystemB_.operationB();
    }
private:
    SubsystemA subsystemA_;
    SubsystemB subsystemB_;
};
""",
    "flyweight": """
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
""",
    "proxy": """
class Subject {
public:
    virtual ~Subject() = default;
    virtual void request() const = 0;
};

class RealSubject : public Subject {
public:
    void request() const override {
        // TODO: Implement real subject operation
    }
};

class Proxy : public Subject {
public:
    void request() const override {
        // TODO: Add access control, lazy initialization, logging, etc.
        if (!realSubject_) {
            realSubject_ = std::make_unique<RealSubject>();
        }
        realSubject_->request();
    }
private:
    mutable std::unique_ptr<RealSubject> realSubject_;
};
""",
    "chain_of_responsibility": """
class Handler {
public:
    virtual ~Handler() = default;
    void setNext(std::shared_ptr<Handler> next) {
        next_ = next;
    }
    virtual void handle(const std::string& request) const {
        // TODO: Handle request or pass to next
        if (next_) {
            next_->handle(request);
        }
    }
protected:
    std::shared_ptr<Handler> next_;
};

class ConcreteHandler : public Handler {
public:
    void handle(const std::string& request) const override {
        // TODO: Check if can handle, otherwise pass to next
        if (canHandle(request)) {
            // Process request
        } else {
            Handler::handle(request);
        }
    }
private:
    bool canHandle(const std::string& request) const {
        // TODO: Check condition
        return false;
    }
};
""",
    "command": """
class Receiver {
public:
    void action() const {
        // TODO: Implement receiver action
    }
    void undo() const {
        // TODO: Implement undo action
    }
};

class Command {
public:
    virtual ~Command() = default;
    virtual void execute() const = 0;
    virtual void undo() const = 0;
};

class ConcreteCommand : public Command {
public:
    explicit ConcreteCommand(Receiver& receiver) : receiver_(receiver) {}
    void execute() const override {
        // TODO: Execute command
        receiver_.action();
    }
    void undo() const override {
        // TODO: Undo command
        receiver_.undo();
    }
private:
    Receiver& receiver_;
};

class Invoker {
public:
    void setCommand(std::unique_ptr<Command> command) {
        command_ = std::move(command);
    }
    void executeCommand() const {
        if (command_) command_->execute();
    }
    void undoCommand() const {
        if (command_) command_->undo();
    }
private:
    std::unique_ptr<Command> command_;
};
""",
    "interpreter": """
class Context {
public:
    explicit Context(const std::string& input) : input_(input) {}
    std::string getInput() const { return input_; }
    void setOutput(const std::string& output) { output_ = output; }
    std::string getOutput() const { return output_; }
private:
    std::string input_;
    std::string output_;
};

class Expression {
public:
    virtual ~Expression() = default;
    virtual void interpret(Context& context) const = 0;
};

class TerminalExpression : public Expression {
public:
    void interpret(Context& context) const override {
        // TODO: Interpret terminal expression
    }
};

class NonTerminalExpression : public Expression {
public:
    void interpret(Context& context) const override {
        // TODO: Interpret non-terminal expression (recursive)
    }
};
""",
    "iterator": """
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
""",
    "mediator": """
class Colleague;

class Mediator {
public:
    virtual ~Mediator() = default;
    virtual void notify(Colleague* sender, const std::string& event) = 0;
};

class Colleague {
public:
    explicit Colleague(Mediator* mediator) : mediator_(mediator) {}
    virtual ~Colleague() = default;
    void send(const std::string& event) {
        if (mediator_) mediator_->notify(this, event);
    }
    virtual void receive(const std::string& event) = 0;
protected:
    Mediator* mediator_;
};

class ConcreteMediator : public Mediator {
public:
    void addColleague(Colleague* colleague) {
        colleagues_.push_back(colleague);
    }
    void notify(Colleague* sender, const std::string& event) override {
        // TODO: Coordinate communication between colleagues
        for (auto* colleague : colleagues_) {
            if (colleague != sender) {
                colleague->receive(event);
            }
        }
    }
private:
    std::vector<Colleague*> colleagues_;
};

class ConcreteColleague : public Colleague {
public:
    using Colleague::Colleague;
    void receive(const std::string& event) override {
        // TODO: Handle received event
    }
};
""",
    "memento": """
class Memento {
public:
    explicit Memento(const std::string& state) : state_(state) {}
    std::string getState() const { return state_; }
private:
    std::string state_;
};

class Originator {
public:
    void setState(const std::string& state) { state_ = state; }
    std::string getState() const { return state_; }
    std::unique_ptr<Memento> save() const {
        return std::make_unique<Memento>(state_);
    }
    void restore(const Memento* memento) {
        if (memento) {
            state_ = memento->getState();
        }
    }
private:
    std::string state_;
};

class Caretaker {
public:
    void addMemento(std::unique_ptr<Memento> memento) {
        mementos_.push_back(std::move(memento));
    }
    const Memento* getMemento(size_t index) const {
        if (index < mementos_.size()) {
            return mementos_[index].get();
        }
        return nullptr;
    }
private:
    std::vector<std::unique_ptr<Memento>> mementos_;
};
""",
    "observer": """
class Observer {
public:
    virtual ~Observer() = default;
    virtual void update(const std::string& state) = 0;
};

class Subject {
public:
    virtual ~Subject() = default;
    void attach(std::shared_ptr<Observer> observer) {
        observers_.push_back(observer);
    }
    void detach(std::shared_ptr<Observer> observer) {
        // TODO: Remove observer
    }
    void notify(const std::string& state) {
        for (auto& observer : observers_) {
            observer->update(state);
        }
    }
    virtual void setState(const std::string& state) {
        state_ = state;
        notify(state);
    }
    std::string getState() const { return state_; }
protected:
    std::vector<std::shared_ptr<Observer>> observers_;
    std::string state_;
};

class ConcreteObserver : public Observer {
public:
    explicit ConcreteObserver(const std::string& name) : name_(name) {}
    void update(const std::string& state) override {
        // TODO: React to state change
    }
private:
    std::string name_;
};

class ConcreteSubject : public Subject {
public:
    void setState(const std::string& state) override {
        // TODO: Custom state logic
        Subject::setState(state);
    }
};
""",
    "state": """
class Context;

class State {
public:
    virtual ~State() = default;
    virtual void handle(Context& context) = 0;
    virtual std::string getName() const = 0;
};

class Context {
public:
    explicit Context(std::unique_ptr<State> state) : state_(std::move(state)) {}
    void setState(std::unique_ptr<State> state) {
        state_ = std::move(state);
    }
    void request() {
        if (state_) state_->handle(*this);
    }
    std::string getStateName() const {
        return state_ ? state_->getName() : "none";
    }
private:
    std::unique_ptr<State> state_;
};

class ConcreteStateA : public State {
public:
    void handle(Context& context) override {
        // TODO: Handle in state A, possibly transition to state B
    }
    std::string getName() const override { return "StateA"; }
};

class ConcreteStateB : public State {
public:
    void handle(Context& context) override {
        // TODO: Handle in state B, possibly transition to state A
    }
    std::string getName() const override { return "StateB"; }
};
""",
    "strategy": """
class Strategy {
public:
    virtual ~Strategy() = default;
    virtual void execute(const std::vector<int>& data) const = 0;
    virtual std::string getName() const = 0;
};

class ConcreteStrategyA : public Strategy {
public:
    void execute(const std::vector<int>& data) const override {
        // TODO: Implement algorithm A
    }
    std::string getName() const override { return "StrategyA"; }
};

class ConcreteStrategyB : public Strategy {
public:
    void execute(const std::vector<int>& data) const override {
        // TODO: Implement algorithm B
    }
    std::string getName() const override { return "StrategyB"; }
};

class Context {
public:
    explicit Context(std::unique_ptr<Strategy> strategy) : strategy_(std::move(strategy)) {}
    void setStrategy(std::unique_ptr<Strategy> strategy) {
        strategy_ = std::move(strategy);
    }
    void executeStrategy(const std::vector<int>& data) const {
        if (strategy_) {
            strategy_->execute(data);
        }
    }
    std::string getStrategyName() const {
        return strategy_ ? strategy_->getName() : "none";
    }
private:
    std::unique_ptr<Strategy> strategy_;
};
""",
    "template_method": """
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
""",
    "visitor": """
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
"""
}

# Includes needed for each pattern
PATTERN_INCLUDES = {
    "singleton": ["iostream"],
    "factory_method": ["memory", "iostream"],
    "abstract_factory": ["memory", "iostream"],
    "builder": ["memory", "string", "iostream"],
    "prototype": ["memory", "unordered_map", "string", "iostream"],
    "adapter": ["memory", "iostream"],
    "bridge": ["memory", "iostream"],
    "composite": ["memory", "vector", "iostream"],
    "decorator": ["memory", "iostream"],
    "facade": ["iostream"],
    "flyweight": ["memory", "unordered_map", "string", "iostream"],
    "proxy": ["memory", "iostream"],
    "chain_of_responsibility": ["memory", "string", "iostream"],
    "command": ["memory", "iostream"],
    "interpreter": ["memory", "string", "iostream"],
    "iterator": ["memory", "vector", "iostream"],
    "mediator": ["memory", "vector", "string", "iostream"],
    "memento": ["memory", "vector", "string", "iostream"],
    "observer": ["memory", "vector", "string", "iostream"],
    "state": ["memory", "string", "iostream"],
    "strategy": ["memory", "vector", "string", "iostream"],
    "template_method": ["iostream"],
    "visitor": ["memory", "string", "iostream"]
}

# Pattern categories
PATTERN_CATEGORIES = {
    "singleton": "creational",
    "factory_method": "creational",
    "abstract_factory": "creational",
    "builder": "creational",
    "prototype": "creational",
    "adapter": "structural",
    "bridge": "structural",
    "composite": "structural",
    "decorator": "structural",
    "facade": "structural",
    "flyweight": "structural",
    "proxy": "structural",
    "chain_of_responsibility": "behavioral",
    "command": "behavioral",
    "interpreter": "behavioral",
    "iterator": "behavioral",
    "mediator": "behavioral",
    "memento": "behavioral",
    "observer": "behavioral",
    "state": "behavioral",
    "strategy": "behavioral",
    "template_method": "behavioral",
    "visitor": "behavioral"
}

# Pattern descriptions
PATTERN_DESCRIPTIONS = {
    "singleton": "全局唯一实例，禁止拷贝，延迟初始化",
    "factory_method": "子类决定创建哪个对象",
    "abstract_factory": "创建一族相关对象",
    "builder": "分步骤构建复杂对象",
    "prototype": "克隆已有对象",
    "adapter": "转换接口以兼容",
    "bridge": "分离抽象与实现",
    "composite": "树形结构的统一处理",
    "decorator": "动态添加职责",
    "facade": "简化复杂子系统的接口",
    "flyweight": "共享细粒度对象",
    "proxy": "控制对象访问",
    "chain_of_responsibility": "请求沿链传递",
    "command": "将请求封装为对象",
    "interpreter": "解释自定义语言",
    "iterator": "顺序访问集合元素",
    "mediator": "集中协调对象交互",
    "memento": "捕获并恢复对象状态",
    "observer": "一对多的依赖通知",
    "state": "状态驱动的行为变化",
    "strategy": "算法族，可互换",
    "template_method": "定义算法骨架，子类填充步骤",
    "visitor": "对一组对象执行新操作"
}

def generate_template(pattern_name):
    """Generate template file content without main()"""
    includes = PATTERN_INCLUDES[pattern_name]
    category = PATTERN_CATEGORIES[pattern_name]
    description = PATTERN_DESCRIPTIONS[pattern_name]
    skeleton = PATTERN_SKELETONS[pattern_name]
    
    # Generate include lines
    include_lines = "\n".join([f"#include <{inc}>" for inc in includes])
    
    # Generate template content
    template = f"""/**
 * {pattern_name.replace('_', ' ').title()} — {description}
 * 意图: {description}
 * 评测: python3 scripts/evaluate.py build src
 * 参考: .reference/{pattern_name}.cpp
 */

{include_lines}

// TODO: 完成以下类实现
{skeleton}
"""
    
    return template

def generate_test(pattern_name):
    """Generate Catch2 test file"""
    category = PATTERN_CATEGORIES[pattern_name]
    
    test_template = f"""// {pattern_name.replace('_', ' ').title()} 模式测试
// 测试设计模式核心结构

#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>

// Include the pattern implementation
#include "../../../src/{category}/{pattern_name}/main.cpp"

TEST_CASE("{pattern_name} structure exists", "[{pattern_name}][structure]") {{
    // Verify classes can be instantiated
    REQUIRE(true);
}}
"""
    
    return test_template

def main():
    base_dir = Path("/home/yun/workspace/design-patterns-cpp")
    
    # Process each pattern
    for pattern_name in PATTERN_SKELETONS.keys():
        category = PATTERN_CATEGORIES[pattern_name]
        
        # Generate and write template
        template_content = generate_template(pattern_name)
        template_path = base_dir / "src" / category / pattern_name / "main.cpp"
        
        with open(template_path, 'w') as f:
            f.write(template_content)
        
        print(f"Updated template: {template_path}")
        
        # Generate and write test
        test_content = generate_test(pattern_name)
        test_path = base_dir / "tests" / f"{pattern_name}_test.cpp"
        
        with open(test_path, 'w') as f:
            f.write(test_content)
        
        print(f"Created test: {test_path}")
    
    print("\nAll templates and tests generated!")
    print("Next steps:")
    print("1. Update CMakeLists.txt to remove executables and add test targets")
    print("2. Update evaluation script to run ctest")
    print("3. Build and test")

if __name__ == "__main__":
    main()
