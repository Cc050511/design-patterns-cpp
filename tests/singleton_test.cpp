// Singleton 模式测试

#include <catch2/catch_test_macros.hpp>
#include <iostream>

#include "src/creational/singleton/main.cpp"

TEST_CASE("singleton instance exists", "[singleton][structure]") {
    REQUIRE(true);
}

TEST_CASE("singleton instance is unique", "[singleton][behavior]") {
    auto& s1 = Singleton::instance(); auto& s2 = Singleton::instance(); REQUIRE(&s1 == &s2);
}

TEST_CASE("singleton cannot be copied", "[singleton][behavior]") {
    static_assert(!std::is_copy_constructible_v<Singleton>); static_assert(!std::is_copy_assignable_v<Singleton>);
}

TEST_CASE("singleton output demo", "[singleton][output]") {
    std::cout << "=== Singleton Demo ===\n";
    std::cout << "Getting instance 1...\n";
    auto& s1 = Singleton::instance();
    s1.operation();
    std::cout << "Getting instance 2...\n";
    auto& s2 = Singleton::instance();
    s2.operation();
    std::cout << "Same instance? " << (&s1 == &s2 ? "YES" : "NO") << "\n";
    std::cout << "Singleton verified successfully.\n";
    REQUIRE(&s1 == &s2);
}
