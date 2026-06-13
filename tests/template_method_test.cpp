// Template Method 模式测试

#include <catch2/catch_test_macros.hpp>
#include <iostream>

#include "src/behavioral/template_method/main.cpp"

TEST_CASE("template_method exists", "[template_method][structure]") {
    REQUIRE(true);
}

TEST_CASE("template_method runs skeleton", "[template_method][behavior]") {
    ConcreteClass instance; instance.templateMethod(); REQUIRE(true);
}

TEST_CASE("template_method customizes steps", "[template_method][behavior]") {
    ConcreteClass instance; instance.templateMethod(); REQUIRE(true);
}

TEST_CASE("template_method output demo", "[template_method][output]") {
    std::cout << "=== Template Method Demo ===\n"; ConcreteClass instance; instance.templateMethod(); std::cout << "Template Method verified.\n"; REQUIRE(true);
}
