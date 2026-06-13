// Memento 模式测试

#include <catch2/catch_test_macros.hpp>
#include <iostream>

#include "src/behavioral/memento/main.cpp"

TEST_CASE("memento exists", "[memento][structure]") {
    REQUIRE(true);
}

TEST_CASE("memento saves state", "[memento][behavior]") {
    Originator originator; originator.setState("State1"); auto memento = originator.save(); REQUIRE(memento != nullptr);
}

TEST_CASE("memento restores state", "[memento][behavior]") {
    Originator originator; originator.setState("State1"); auto memento = originator.save(); originator.setState("State2"); originator.restore(memento.get()); REQUIRE(originator.getState() == "State1");
}

TEST_CASE("memento output demo", "[memento][output]") {
    std::cout << "=== Memento Demo ===\n"; Originator originator; originator.setState("State1"); auto memento = originator.save(); originator.setState("State2"); originator.restore(memento.get()); std::cout << "Memento verified.\n"; REQUIRE(originator.getState() == "State1");
}
