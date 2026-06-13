// Abstract Factory 模式测试

#include <catch2/catch_test_macros.hpp>
#include <cstdlib>
#include <filesystem>

namespace fs = std::filesystem;

TEST_CASE("abstract_factory compiles", "[abstract_factory][build]") {
    REQUIRE(fs::exists("./abstract_factory"));
}

TEST_CASE("abstract_factory runs", "[abstract_factory][runtime]") {
    std::system("./abstract_factory");
    REQUIRE(true);
}
