// Builder 模式测试

#include <catch2/catch_test_macros.hpp>
#include <iostream>

#include "src/creational/builder/main.cpp"

TEST_CASE("builder exists", "[builder][structure]") {
    REQUIRE(true);
}

TEST_CASE("builder constructs product", "[builder][behavior]") {
    ConcreteBuilder builder; Director director(builder); director.construct(); auto product = builder.getResult(); REQUIRE(product != nullptr);
}

TEST_CASE("builder step by step", "[builder][behavior]") {
    ConcreteBuilder builder; builder.buildPartA(); builder.buildPartB(); auto product = builder.getResult(); REQUIRE(product != nullptr);
}

TEST_CASE("builder output demo", "[builder][output]") {
    std::cout << "=== Builder Demo ===\n"; ConcreteBuilder builder; Director director(builder); director.construct(); auto product = builder.getResult(); std::cout << "Builder verified.\n"; REQUIRE(product != nullptr);
}
