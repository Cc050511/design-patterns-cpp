// Template Method 模式测试

#include <catch2/catch_test_macros.hpp>
#include <cstdlib>
#include <filesystem>

namespace fs = std::filesystem;

TEST_CASE("template_method compiles", "[template_method][build]") {
    REQUIRE(fs::exists("../template_method"));
}

TEST_CASE("template_method runs", "[template_method][runtime]") {
    std::system("../template_method");
    REQUIRE(true);
}
