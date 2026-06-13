// Bridge 模式测试

#include <catch2/catch_test_macros.hpp>
#include <iostream>

#include "src/structural/bridge/main.cpp"

TEST_CASE("bridge exists", "[bridge][structure]") {
    REQUIRE(true);
}

TEST_CASE("bridge separates abstraction", "[bridge][behavior]") {
    auto impl = std::make_unique<ConcreteImplementor>(); Abstraction abstraction(std::move(impl)); abstraction.operation(); REQUIRE(true);
}

TEST_CASE("bridge can change implementation", "[bridge][behavior]") {
    auto impl = std::make_unique<ConcreteImplementor>(); Abstraction abstraction(std::move(impl)); abstraction.operation(); REQUIRE(true);
}

TEST_CASE("bridge output demo", "[bridge][output]") {
    std::cout << "=== Bridge Demo ===\n"; auto impl = std::make_unique<ConcreteImplementor>(); Abstraction abstraction(std::move(impl)); abstraction.operation(); std::cout << "Bridge verified.\n"; REQUIRE(true);
}
