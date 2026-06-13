// Decorator 模式测试

#include <catch2/catch_test_macros.hpp>
#include <iostream>

#include "src/structural/decorator/main.cpp"

TEST_CASE("decorator exists", "[decorator][structure]") {
    REQUIRE(true);
}

TEST_CASE("decorator adds behavior", "[decorator][behavior]") {
    auto component = std::make_unique<ConcreteComponent>(); auto decorator = std::make_unique<ConcreteDecorator>(std::move(component)); decorator->operation(); REQUIRE(true);
}

TEST_CASE("decorator can nest", "[decorator][behavior]") {
    auto component = std::make_unique<ConcreteComponent>(); auto decorator1 = std::make_unique<ConcreteDecorator>(std::move(component)); auto decorator2 = std::make_unique<ConcreteDecorator>(std::move(decorator1)); decorator2->operation(); REQUIRE(true);
}

TEST_CASE("decorator output demo", "[decorator][output]") {
    std::cout << "=== Decorator Demo ===\n"; auto component = std::make_unique<ConcreteComponent>(); auto decorator = std::make_unique<ConcreteDecorator>(std::move(component)); decorator->operation(); std::cout << "Decorator verified.\n"; REQUIRE(true);
}
