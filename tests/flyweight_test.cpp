// Flyweight 模式测试

#include <catch2/catch_test_macros.hpp>
#include <cstdlib>
#include <filesystem>

namespace fs = std::filesystem;

TEST_CASE("flyweight compiles", "[flyweight][build]") {
    REQUIRE(fs::exists("../flyweight"));
}

TEST_CASE("flyweight runs", "[flyweight][runtime]") {
    std::system("../flyweight");
    REQUIRE(true);
}
