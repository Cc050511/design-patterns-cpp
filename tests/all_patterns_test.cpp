// 统一测试入口：所有模式核心行为验证
// 由于每个模式是独立可执行文件，这里测试通过编译+运行检查来验证
// 更深入的单元测试需要模式实现，目前先验证框架

#include <catch2/catch_test_macros.hpp>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <string>

namespace fs = std::filesystem;

static std::string run_demo(const std::string& name) {
    const fs::path binary = fs::path(BINARY_DIR) / name;
    if (!fs::exists(binary)) {
        FAIL("Binary not found: " << binary);
    }
    // 使用 popen 运行并捕获输出
    FILE* pipe = popen(binary.string().c_str(), "r");
    REQUIRE(pipe != nullptr);
    std::string output;
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
        output += buffer;
    }
    pclose(pipe);
    return output;
}

TEST_CASE("All 23 pattern binaries exist", "[build]") {
    const std::vector<std::string> patterns = {
        "singleton", "factory_method", "abstract_factory", "builder", "prototype",
        "adapter", "bridge", "composite", "decorator", "facade", "flyweight", "proxy",
        "chain_of_responsibility", "command", "interpreter", "iterator", "mediator",
        "memento", "observer", "state", "strategy", "template_method", "visitor"
    };
    const fs::path build_dir = fs::path(BINARY_DIR);
    for (const auto& p : patterns) {
        INFO("Checking binary: " << p);
        REQUIRE(fs::exists(build_dir / p));
    }
}

TEST_CASE("Singleton pattern basics", "[singleton]") {
    auto output = run_demo("singleton");
    REQUIRE(output.find("Singleton") != std::string::npos);
    REQUIRE(output.find("TODO") == std::string::npos);
}

TEST_CASE("Observer pattern basics", "[observer]") {
    auto output = run_demo("observer");
    REQUIRE(output.find("Observer") != std::string::npos);
    REQUIRE(output.find("TODO") == std::string::npos);
}

TEST_CASE("Strategy pattern basics", "[strategy]") {
    auto output = run_demo("strategy");
    REQUIRE(output.find("Strategy") != std::string::npos);
    REQUIRE(output.find("TODO") == std::string::npos);
}

TEST_CASE("Command pattern basics", "[command]") {
    auto output = run_demo("command");
    REQUIRE(output.find("Command") != std::string::npos);
    REQUIRE(output.find("TODO") == std::string::npos);
}

TEST_CASE("State pattern basics", "[state]") {
    auto output = run_demo("state");
    REQUIRE(output.find("State") != std::string::npos);
    REQUIRE(output.find("TODO") == std::string::npos);
}

TEST_CASE("Decorator pattern basics", "[decorator]") {
    auto output = run_demo("decorator");
    REQUIRE(output.find("Decorator") != std::string::npos);
    REQUIRE(output.find("TODO") == std::string::npos);
}

TEST_CASE("Builder pattern basics", "[builder]") {
    auto output = run_demo("builder");
    REQUIRE(output.find("Builder") != std::string::npos);
    REQUIRE(output.find("TODO") == std::string::npos);
}

TEST_CASE("Adapter pattern basics", "[adapter]") {
    auto output = run_demo("adapter");
    REQUIRE(output.find("Adapter") != std::string::npos);
    REQUIRE(output.find("TODO") == std::string::npos);
}

TEST_CASE("Visitor pattern basics", "[visitor]") {
    auto output = run_demo("visitor");
    REQUIRE(output.find("Visitor") != std::string::npos);
    REQUIRE(output.find("TODO") == std::string::npos);
}
