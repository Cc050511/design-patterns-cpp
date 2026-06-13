// Iterator 模式测试

#include <catch2/catch_test_macros.hpp>
#include <iostream>

#include "src/behavioral/iterator/main.cpp"

TEST_CASE("iterator exists", "[iterator][structure]") {
    REQUIRE(true);
}

TEST_CASE("iterator traverses collection", "[iterator][behavior]") {
    ConcreteAggregate aggregate; aggregate.add(1); aggregate.add(2); auto it = aggregate.createIterator(); REQUIRE(it->hasNext()); REQUIRE(it->next() == 1);
}

TEST_CASE("iterator sequential access", "[iterator][behavior]") {
    ConcreteAggregate aggregate; aggregate.add(1); aggregate.add(2); aggregate.add(3); auto it = aggregate.createIterator(); int sum = 0; while (it->hasNext()) { sum += it->next(); } REQUIRE(sum == 6);
}

TEST_CASE("iterator output demo", "[iterator][output]") {
    std::cout << "=== Iterator Demo ===\n"; ConcreteAggregate aggregate; aggregate.add(1); aggregate.add(2); aggregate.add(3); auto it = aggregate.createIterator(); while (it->hasNext()) { std::cout << "Element: " << it->next() << "\n"; } std::cout << "Iterator verified.\n"; REQUIRE(true);
}
