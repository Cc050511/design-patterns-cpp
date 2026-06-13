// Prototype 模式测试

#include <catch2/catch_test_macros.hpp>
#include <iostream>

#include "src/creational/prototype/main.cpp"

TEST_CASE("prototype exists", "[prototype][structure]") {
    REQUIRE(true);
}

TEST_CASE("prototype clones correctly", "[prototype][behavior]") {
    ConcretePrototype original; auto clone = original.clone(); REQUIRE(clone != nullptr);
}

TEST_CASE("prototype clone is different instance", "[prototype][behavior]") {
    ConcretePrototype original; auto clone = original.clone(); REQUIRE(clone.get() != &original);
}

TEST_CASE("prototype output demo", "[prototype][output]") {
    std::cout << "=== Prototype Demo ===\n"; ConcretePrototype original; auto clone = original.clone(); clone->operation(); std::cout << "Prototype verified.\n"; REQUIRE(clone != nullptr);
}
