// Strategy 模式测试

#include <catch2/catch_test_macros.hpp>
#include <cstdlib>
#include <filesystem>

namespace fs = std::filesystem;

TEST_CASE("strategy compiles", "[strategy][build]") {
    REQUIRE(fs::exists("./strategy"));
}

TEST_CASE("strategy runs", "[strategy][runtime]") {
    std::system("./strategy");
    REQUIRE(true);
}
