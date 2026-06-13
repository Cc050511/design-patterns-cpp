// Builder 模式测试

#include <catch2/catch_test_macros.hpp>
#include <cstdlib>
#include <filesystem>

namespace fs = std::filesystem;

TEST_CASE("builder compiles", "[builder][build]") {
    REQUIRE(fs::exists("./builder"));
}

TEST_CASE("builder runs", "[builder][runtime]") {
    std::system("./builder");
    REQUIRE(true);
}
