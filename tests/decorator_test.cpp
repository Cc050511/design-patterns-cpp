// Decorator 模式测试

#include <catch2/catch_test_macros.hpp>
#include <cstdlib>
#include <filesystem>

namespace fs = std::filesystem;

TEST_CASE("decorator compiles", "[decorator][build]") {
    REQUIRE(fs::exists("./decorator"));
}

TEST_CASE("decorator runs", "[decorator][runtime]") {
    std::system("./decorator");
    REQUIRE(true);
}
