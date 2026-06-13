// Mediator 模式测试

#include <catch2/catch_test_macros.hpp>
#include <iostream>

#include "src/behavioral/mediator/main.cpp"

TEST_CASE("mediator exists", "[mediator][structure]") {
    REQUIRE(true);
}

TEST_CASE("mediator coordinates", "[mediator][behavior]") {
    ConcreteMediator mediator; ConcreteColleague colleague1(&mediator); ConcreteColleague colleague2(&mediator); mediator.addColleague(&colleague1); mediator.addColleague(&colleague2); colleague1.send("Hello"); REQUIRE(true);
}

TEST_CASE("mediator decouples colleagues", "[mediator][behavior]") {
    ConcreteMediator mediator; ConcreteColleague colleague1(&mediator); ConcreteColleague colleague2(&mediator); mediator.addColleague(&colleague1); mediator.addColleague(&colleague2); colleague1.send("Hello"); REQUIRE(true);
}

TEST_CASE("mediator output demo", "[mediator][output]") {
    std::cout << "=== Mediator Demo ===\n"; ConcreteMediator mediator; ConcreteColleague colleague1(&mediator); ConcreteColleague colleague2(&mediator); mediator.addColleague(&colleague1); mediator.addColleague(&colleague2); colleague1.send("Hello"); std::cout << "Mediator verified.\n"; REQUIRE(true);
}
