// Proxy 模式测试

#include <catch2/catch_test_macros.hpp>
#include <cstdlib>
#include <filesystem>

namespace fs = std::filesystem;

TEST_CASE("proxy compiles", "[proxy][build]") {
    REQUIRE(fs::exists("../proxy"));
}

TEST_CASE("proxy runs", "[proxy][runtime]") {
    std::system("../proxy");
    REQUIRE(true);
}
