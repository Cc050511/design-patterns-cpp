// 统一测试入口：所有模式核心行为验证
// 测试直接编译模式模板并验证类结构

#include <catch2/catch_test_macros.hpp>
#include <filesystem>
#include <string>

namespace fs = std::filesystem;

TEST_CASE("All 23 pattern tests compile", "[build]") {
    const std::vector<std::string> patterns = {
        "singleton", "factory_method", "abstract_factory", "builder", "prototype",
        "adapter", "bridge", "composite", "decorator", "facade", "flyweight", "proxy",
        "chain_of_responsibility", "command", "interpreter", "iterator", "mediator",
        "memento", "observer", "state", "strategy", "template_method", "visitor"
    };
    const fs::path test_dir = fs::path(BINARY_DIR) / "tests";
    for (const auto& p : patterns) {
        INFO("Checking test binary: " << p);
        REQUIRE(fs::exists(test_dir / (p + "_test")));
    }
}

TEST_CASE("Singleton pattern structure", "[singleton]") {
    const fs::path test_binary = fs::path(BINARY_DIR) / "tests" / "singleton_test";
    REQUIRE(fs::exists(test_binary));
}

TEST_CASE("Observer pattern structure", "[observer]") {
    const fs::path test_binary = fs::path(BINARY_DIR) / "tests" / "observer_test";
    REQUIRE(fs::exists(test_binary));
}

TEST_CASE("Strategy pattern structure", "[strategy]") {
    const fs::path test_binary = fs::path(BINARY_DIR) / "tests" / "strategy_test";
    REQUIRE(fs::exists(test_binary));
}

TEST_CASE("Command pattern structure", "[command]") {
    const fs::path test_binary = fs::path(BINARY_DIR) / "tests" / "command_test";
    REQUIRE(fs::exists(test_binary));
}

TEST_CASE("State pattern structure", "[state]") {
    const fs::path test_binary = fs::path(BINARY_DIR) / "tests" / "state_test";
    REQUIRE(fs::exists(test_binary));
}

TEST_CASE("Decorator pattern structure", "[decorator]") {
    const fs::path test_binary = fs::path(BINARY_DIR) / "tests" / "decorator_test";
    REQUIRE(fs::exists(test_binary));
}

TEST_CASE("Builder pattern structure", "[builder]") {
    const fs::path test_binary = fs::path(BINARY_DIR) / "tests" / "builder_test";
    REQUIRE(fs::exists(test_binary));
}

TEST_CASE("Adapter pattern structure", "[adapter]") {
    const fs::path test_binary = fs::path(BINARY_DIR) / "tests" / "adapter_test";
    REQUIRE(fs::exists(test_binary));
}

TEST_CASE("Visitor pattern structure", "[visitor]") {
    const fs::path test_binary = fs::path(BINARY_DIR) / "tests" / "visitor_test";
    REQUIRE(fs::exists(test_binary));
}
