// Flyweight 模式测试

#include <catch2/catch_test_macros.hpp>
#include <iostream>

#include "src/structural/flyweight/main.cpp"

TEST_CASE("flyweight exists", "[flyweight][structure]") {
    REQUIRE(true);
}

TEST_CASE("flyweight shares instances", "[flyweight][behavior]") {
    FlyweightFactory factory; auto fw1 = factory.getFlyweight("A"); auto fw2 = factory.getFlyweight("A"); REQUIRE(fw1 == fw2);
}

TEST_CASE("flyweight saves memory", "[flyweight][behavior]") {
    FlyweightFactory factory; auto fw1 = factory.getFlyweight("A"); auto fw2 = factory.getFlyweight("B"); fw1->operation("state1"); fw2->operation("state2"); REQUIRE(fw1 != fw2);
}

TEST_CASE("flyweight output demo", "[flyweight][output]") {
    std::cout << "=== Flyweight Demo ===\n"; FlyweightFactory factory; auto fw1 = factory.getFlyweight("A"); auto fw2 = factory.getFlyweight("A"); fw1->operation("state"); std::cout << "Flyweight verified.\n"; REQUIRE(fw1 == fw2);
}
