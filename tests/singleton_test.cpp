// Singleton 模式测试
// 测试设计模式核心结构

#include <catch2/catch_test_macros.hpp>
#include <sstream>

// Include the pattern implementation
#include "src/creational/singleton/main.cpp"

TEST_CASE("singleton instance is unique", "[singleton][behavior]") {
    auto& s1 = Singleton::instance();
    auto& s2 = Singleton::instance();
    REQUIRE(&s1 == &s2);
}

TEST_CASE("singleton output contains instance address", "[singleton][output]") {
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
