// Bridge 模式测试

#include <catch2/catch_test_macros.hpp>
#include <cstdlib>
#include <filesystem>

namespace fs = std::filesystem;

TEST_CASE("bridge compiles", "[bridge][build]") {
    REQUIRE(fs::exists("../bridge"));
}

TEST_CASE("bridge runs", "[bridge][runtime]") {
    std::system("../bridge");
    REQUIRE(true);
}
