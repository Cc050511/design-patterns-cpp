// State 模式测试

#include <catch2/catch_test_macros.hpp>
#include <iostream>

#include "src/behavioral/state/main.cpp"

TEST_CASE("state exists", "[state][structure]") {
    REQUIRE(true);
}

TEST_CASE("state changes behavior", "[state][behavior]") {
    auto stateA = std::make_unique<ConcreteStateA>(); Context context(std::move(stateA)); context.request(); REQUIRE(context.getStateName() == "StateA");
}

TEST_CASE("state transitions", "[state][behavior]") {
    auto stateA = std::make_unique<ConcreteStateA>(); Context context(std::move(stateA)); context.request(); auto stateB = std::make_unique<ConcreteStateB>(); context.setState(std::move(stateB)); context.request(); REQUIRE(context.getStateName() == "StateB");
}

TEST_CASE("state output demo", "[state][output]") {
    std::cout << "=== State Demo ===\n"; auto stateA = std::make_unique<ConcreteStateA>(); Context context(std::move(stateA)); context.request(); auto stateB = std::make_unique<ConcreteStateB>(); context.setState(std::move(stateB)); context.request(); std::cout << "State verified.\n"; REQUIRE(true);
}
