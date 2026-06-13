/**
 * Facade — 简化复杂子系统的接口
 * 意图: 简化复杂子系统的接口
 * 评测: python3 scripts/evaluate.py build src
 * 参考: .reference/facade.cpp
 */

#include <iostream>

// TODO: 完成以下类实现

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

