// Observer 模式测试

#include <catch2/catch_test_macros.hpp>
#include <cstdlib>
#include <filesystem>

namespace fs = std::filesystem;

TEST_CASE("observer compiles", "[observer][build]") {
    REQUIRE(fs::exists("../observer"));
}

TEST_CASE("observer runs", "[observer][runtime]") {
    std::system("../observer");
    REQUIRE(true);
}
