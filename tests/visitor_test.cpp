// Visitor 模式测试

#include <catch2/catch_test_macros.hpp>
#include <cstdlib>
#include <filesystem>

namespace fs = std::filesystem;

TEST_CASE("visitor compiles", "[visitor][build]") {
    REQUIRE(fs::exists("../visitor"));
}

TEST_CASE("visitor runs", "[visitor][runtime]") {
    std::system("../visitor");
    REQUIRE(true);
}
