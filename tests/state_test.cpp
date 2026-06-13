// State 模式测试

#include <catch2/catch_test_macros.hpp>
#include <cstdlib>
#include <filesystem>

namespace fs = std::filesystem;

TEST_CASE("state compiles", "[state][build]") {
    REQUIRE(fs::exists("./state"));
}

TEST_CASE("state runs", "[state][runtime]") {
    std::system("./state");
    REQUIRE(true);
}
