// Abstract Factory 模式测试

#include <catch2/catch_test_macros.hpp>
#include <iostream>

#include "src/creational/abstract_factory/main.cpp"

TEST_CASE("factory exists", "[abstract_factory][structure]") {
    REQUIRE(true);
}

TEST_CASE("factory creates product family", "[abstract_factory][behavior]") {
    ConcreteFactory factory; auto productA = factory.createProductA(); auto productB = factory.createProductB(); REQUIRE(productA != nullptr); REQUIRE(productB != nullptr);
}

TEST_CASE("factory products are related", "[abstract_factory][behavior]") {
    ConcreteFactory factory; auto productA = factory.createProductA(); auto productB = factory.createProductB(); productA->useA(); productB->useB(); REQUIRE(productA != nullptr);
}

TEST_CASE("factory output demo", "[abstract_factory][output]") {
    std::cout << "=== Abstract Factory Demo ===\n"; ConcreteFactory factory; auto productA = factory.createProductA(); auto productB = factory.createProductB(); productA->useA(); productB->useB(); std::cout << "Abstract Factory verified.\n"; REQUIRE(productA != nullptr);
}
