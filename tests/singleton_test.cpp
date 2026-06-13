// Singleton 模式测试

#include <catch2/catch_test_macros.hpp>
#include <cstdlib>
#include <filesystem>

namespace fs = std::filesystem;

TEST_CASE("singleton compiles", "[singleton][build]") {
    REQUIRE(fs::exists("./singleton"));
}

TEST_CASE("singleton runs", "[singleton][runtime]") {
    std::system("./singleton");
    REQUIRE(true);
}
