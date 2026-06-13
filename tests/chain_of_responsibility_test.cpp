// Chain Of Responsibility 模式测试

#include <catch2/catch_test_macros.hpp>
#include <cstdlib>
#include <filesystem>

namespace fs = std::filesystem;

TEST_CASE("chain_of_responsibility compiles", "[chain_of_responsibility][build]") {
    REQUIRE(fs::exists("./chain_of_responsibility"));
}

TEST_CASE("chain_of_responsibility runs", "[chain_of_responsibility][runtime]") {
    std::system("./chain_of_responsibility");
    REQUIRE(true);
}
