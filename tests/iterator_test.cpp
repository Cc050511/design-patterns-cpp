// Iterator 模式测试

#include <catch2/catch_test_macros.hpp>
#include <cstdlib>
#include <filesystem>

namespace fs = std::filesystem;

TEST_CASE("iterator compiles", "[iterator][build]") {
    REQUIRE(fs::exists("./iterator"));
}

TEST_CASE("iterator runs", "[iterator][runtime]") {
    std::system("./iterator");
    REQUIRE(true);
}
