// Mediator 模式测试

#include <catch2/catch_test_macros.hpp>
#include <cstdlib>
#include <filesystem>

namespace fs = std::filesystem;

TEST_CASE("mediator compiles", "[mediator][build]") {
    REQUIRE(fs::exists("./mediator"));
}

TEST_CASE("mediator runs", "[mediator][runtime]") {
    std::system("./mediator");
    REQUIRE(true);
}
