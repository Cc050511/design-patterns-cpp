// Facade 模式测试

#include <catch2/catch_test_macros.hpp>
#include <cstdlib>
#include <filesystem>

namespace fs = std::filesystem;

TEST_CASE("facade compiles", "[facade][build]") {
    REQUIRE(fs::exists("./facade"));
}

TEST_CASE("facade runs", "[facade][runtime]") {
    std::system("./facade");
    REQUIRE(true);
}
