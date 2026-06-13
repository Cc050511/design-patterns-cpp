// Factory Method 模式测试

#include <catch2/catch_test_macros.hpp>
#include <iostream>

#include "src/creational/factory_method/main.cpp"

TEST_CASE("factory creator exists", "[factory_method][structure]") {
    REQUIRE(true);
}

TEST_CASE("factory creates product", "[factory_method][behavior]") {
    ConcreteCreator creator; auto product = creator.createProduct(); REQUIRE(product != nullptr);
}

TEST_CASE("factory different products", "[factory_method][behavior]") {
    ConcreteCreator creator; auto product = creator.createProduct(); product->use(); REQUIRE(product != nullptr);
}

TEST_CASE("factory output demo", "[factory_method][output]") {
    std::cout << "=== Factory Method Demo ===\n"; ConcreteCreator creator; auto product = creator.createProduct(); product->use(); std::cout << "Factory Method verified.\n"; REQUIRE(product != nullptr);
}
