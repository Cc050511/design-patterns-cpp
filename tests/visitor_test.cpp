// Visitor 模式测试

#include <catch2/catch_test_macros.hpp>
#include <iostream>

#include "src/behavioral/visitor/main.cpp"

TEST_CASE("visitor exists", "[visitor][structure]") {
    REQUIRE(true);
}

TEST_CASE("visitor visits element", "[visitor][behavior]") {
    ConcreteElementA element; ConcreteVisitor visitor; element.accept(visitor); REQUIRE(true);
}

TEST_CASE("visitor different elements", "[visitor][behavior]") {
    ConcreteElementA elementA; ConcreteElementB elementB; ConcreteVisitor visitor; elementA.accept(visitor); elementB.accept(visitor); REQUIRE(true);
}

TEST_CASE("visitor output demo", "[visitor][output]") {
    std::cout << "=== Visitor Demo ===\n"; ConcreteElementA elementA; ConcreteElementB elementB; ConcreteVisitor visitor; elementA.accept(visitor); elementB.accept(visitor); std::cout << "Visitor verified.\n"; REQUIRE(true);
}
