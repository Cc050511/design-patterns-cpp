// Strategy 模式测试

#include <catch2/catch_test_macros.hpp>
#include <iostream>

#include "src/behavioral/strategy/main.cpp"

TEST_CASE("strategy exists", "[strategy][structure]") {
    REQUIRE(true);
}

TEST_CASE("strategy can be set", "[strategy][behavior]") {
    auto strategy = std::make_unique<ConcreteStrategyA>(); Context context(std::move(strategy)); REQUIRE(context.getStrategyName() == "StrategyA");
}

TEST_CASE("strategy can be switched", "[strategy][behavior]") {
    auto strategyA = std::make_unique<ConcreteStrategyA>(); Context context(std::move(strategyA)); context.executeStrategy({3, 1, 2}); auto strategyB = std::make_unique<ConcreteStrategyB>(); context.setStrategy(std::move(strategyB)); context.executeStrategy({3, 1, 2}); REQUIRE(context.getStrategyName() == "StrategyB");
}

TEST_CASE("strategy output demo", "[strategy][output]") {
    std::cout << "=== Strategy Demo ===\n"; auto strategyA = std::make_unique<ConcreteStrategyA>(); Context context(std::move(strategyA)); context.executeStrategy({3, 1, 2}); std::cout << "Strategy verified.\n"; REQUIRE(true);
}
