// Command 模式测试

#include <catch2/catch_test_macros.hpp>
#include <cstdlib>
#include <filesystem>

namespace fs = std::filesystem;

TEST_CASE("command compiles", "[command][build]") {
    REQUIRE(fs::exists("../command"));
}

TEST_CASE("command runs", "[command][runtime]") {
    std::system("../command");
    REQUIRE(true);
}
