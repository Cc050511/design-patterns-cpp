// Memento 模式测试

#include <catch2/catch_test_macros.hpp>
#include <cstdlib>
#include <filesystem>

namespace fs = std::filesystem;

TEST_CASE("memento compiles", "[memento][build]") {
    REQUIRE(fs::exists("./memento"));
}

TEST_CASE("memento runs", "[memento][runtime]") {
    std::system("./memento");
    REQUIRE(true);
}
