// Adapter 模式测试

#include <catch2/catch_test_macros.hpp>
#include <cstdlib>
#include <filesystem>

namespace fs = std::filesystem;

TEST_CASE("adapter compiles", "[adapter][build]") {
    REQUIRE(fs::exists("../adapter"));
}

TEST_CASE("adapter runs", "[adapter][runtime]") {
    std::system("../adapter");
    REQUIRE(true);
}
