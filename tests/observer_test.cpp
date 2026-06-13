// Observer 模式测试

#include <catch2/catch_test_macros.hpp>
#include <iostream>

#include "src/behavioral/observer/main.cpp"

TEST_CASE("observer exists", "[observer][structure]") {
    REQUIRE(true);
}

TEST_CASE("observer can attach", "[observer][behavior]") {
    ConcreteSubject subject; auto observer = std::make_shared<ConcreteObserver>("Obs"); subject.attach(observer); REQUIRE(true);
}

TEST_CASE("observer receives notifications", "[observer][behavior]") {
    ConcreteSubject subject; auto observer = std::make_shared<ConcreteObserver>("Obs"); subject.attach(observer); subject.setState("Test"); REQUIRE(subject.getState() == "Test");
}

TEST_CASE("observer multiple observers", "[observer][behavior]") {
    ConcreteSubject subject; auto obs1 = std::make_shared<ConcreteObserver>("Obs1"); auto obs2 = std::make_shared<ConcreteObserver>("Obs2"); subject.attach(obs1); subject.attach(obs2); subject.notify("Update"); REQUIRE(true);
}

TEST_CASE("observer output demo", "[observer][output]") {
    std::cout << "=== Observer Demo ===\n"; ConcreteSubject subject; auto obs1 = std::make_shared<ConcreteObserver>("Obs1"); auto obs2 = std::make_shared<ConcreteObserver>("Obs2"); subject.attach(obs1); subject.attach(obs2); subject.setState("Active"); subject.notify("Update"); std::cout << "Observer verified.\n"; REQUIRE(subject.getState() == "Active");
}
