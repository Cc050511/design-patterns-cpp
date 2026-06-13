// Factory Method 模式测试

#include <catch2/catch_test_macros.hpp>
#include <cstdlib>
#include <filesystem>

namespace fs = std::filesystem;

TEST_CASE("factory_method compiles", "[factory_method][build]") {
    REQUIRE(fs::exists("./factory_method"));
}

TEST_CASE("factory_method runs", "[factory_method][runtime]") {
    std::system("./factory_method");
    REQUIRE(true);
}
