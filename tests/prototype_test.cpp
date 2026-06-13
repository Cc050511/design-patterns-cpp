// Prototype 模式测试

#include <catch2/catch_test_macros.hpp>
#include <cstdlib>
#include <filesystem>

namespace fs = std::filesystem;

TEST_CASE("prototype compiles", "[prototype][build]") {
    REQUIRE(fs::exists("./prototype"));
}

TEST_CASE("prototype runs", "[prototype][runtime]") {
    std::system("./prototype");
    REQUIRE(true);
}
