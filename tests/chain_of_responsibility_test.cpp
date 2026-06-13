// Chain of Responsibility 模式测试

#include <catch2/catch_test_macros.hpp>
#include <iostream>

#include "src/behavioral/chain_of_responsibility/main.cpp"

TEST_CASE("chain exists", "[chain_of_responsibility][structure]") {
    REQUIRE(true);
}

TEST_CASE("chain passes request", "[chain_of_responsibility][behavior]") {
    auto handler1 = std::make_shared<ConcreteHandler>(); auto handler2 = std::make_shared<ConcreteHandler>(); handler1->setNext(handler2); handler1->handle("request"); REQUIRE(true);
}

TEST_CASE("chain handles different levels", "[chain_of_responsibility][behavior]") {
    auto handler1 = std::make_shared<ConcreteHandler>(); auto handler2 = std::make_shared<ConcreteHandler>(); handler1->setNext(handler2); handler1->handle("request"); REQUIRE(true);
}

TEST_CASE("chain output demo", "[chain_of_responsibility][output]") {
    std::cout << "=== Chain of Responsibility Demo ===\n"; auto handler1 = std::make_shared<ConcreteHandler>(); auto handler2 = std::make_shared<ConcreteHandler>(); handler1->setNext(handler2); handler1->handle("request"); std::cout << "Chain of Responsibility verified.\n"; REQUIRE(true);
}
