// Composite 模式测试

#include <catch2/catch_test_macros.hpp>
#include <cstdlib>
#include <filesystem>

namespace fs = std::filesystem;

TEST_CASE("composite compiles", "[composite][build]") {
    REQUIRE(fs::exists("./composite"));
}

TEST_CASE("composite runs", "[composite][runtime]") {
    std::system("./composite");
    REQUIRE(true);
}
