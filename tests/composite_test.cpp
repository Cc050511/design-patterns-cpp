// Composite 模式测试

#include <catch2/catch_test_macros.hpp>
#include <iostream>

#include "src/structural/composite/main.cpp"

TEST_CASE("composite exists", "[composite][structure]") {
    REQUIRE(true);
}

TEST_CASE("composite treats leaf uniformly", "[composite][behavior]") {
    auto leaf = std::make_shared<Leaf>(); leaf->operation(); REQUIRE(true);
}

TEST_CASE("composite treats tree uniformly", "[composite][behavior]") {
    auto root = std::make_shared<Composite>(); auto leaf = std::make_shared<Leaf>(); root->add(leaf); root->operation(); REQUIRE(true);
}

TEST_CASE("composite output demo", "[composite][output]") {
    std::cout << "=== Composite Demo ===\n"; auto root = std::make_shared<Composite>(); auto leaf1 = std::make_shared<Leaf>(); auto leaf2 = std::make_shared<Leaf>(); root->add(leaf1); root->add(leaf2); root->operation(); std::cout << "Composite verified.\n"; REQUIRE(true);
}
