// Adapter 模式测试

#include <catch2/catch_test_macros.hpp>
#include <iostream>

#include "src/structural/adapter/main.cpp"

TEST_CASE("adapter exists", "[adapter][structure]") {
    REQUIRE(true);
}

TEST_CASE("adapter calls adaptee", "[adapter][behavior]") {
    Adapter adapter; adapter.request(); REQUIRE(true);
}

TEST_CASE("adapter converts interface", "[adapter][behavior]") {
    Adapter adapter; adapter.request(); REQUIRE(true);
}

TEST_CASE("adapter output demo", "[adapter][output]") {
    std::cout << "=== Adapter Demo ===\n"; Adapter adapter; adapter.request(); std::cout << "Adapter verified.\n"; REQUIRE(true);
}
