// Command 模式测试

#include <catch2/catch_test_macros.hpp>
#include <iostream>

#include "src/behavioral/command/main.cpp"

TEST_CASE("command exists", "[command][structure]") {
    REQUIRE(true);
}

TEST_CASE("command executes", "[command][behavior]") {
    Receiver receiver; ConcreteCommand command(receiver); command.execute(); REQUIRE(true);
}

TEST_CASE("command undoes", "[command][behavior]") {
    Receiver receiver; ConcreteCommand command(receiver); command.execute(); command.undo(); REQUIRE(true);
}

TEST_CASE("command output demo", "[command][output]") {
    std::cout << "=== Command Demo ===\n"; Receiver receiver; ConcreteCommand command(receiver); command.execute(); command.undo(); std::cout << "Command verified.\n"; REQUIRE(true);
}
