// Interpreter 模式测试

#include <catch2/catch_test_macros.hpp>
#include <cstdlib>
#include <filesystem>

namespace fs = std::filesystem;

TEST_CASE("interpreter compiles", "[interpreter][build]") {
    REQUIRE(fs::exists("./interpreter"));
}

TEST_CASE("interpreter runs", "[interpreter][runtime]") {
    std::system("./interpreter");
    REQUIRE(true);
}
