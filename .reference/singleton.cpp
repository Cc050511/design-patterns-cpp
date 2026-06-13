#include <iostream>
#include <memory>
#include <string>

// === Singleton Demo ===
// Ensures a class has only one instance and provides global access to it.

class Logger {
public:
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;
    Logger(Logger&&) = delete;
    Logger& operator=(Logger&&) = delete;

    static Logger& getInstance() {
        static Logger instance;
        return instance;
    }

    void log(const std::string& message) {
        std::cout << "[LOG] " << message << std::endl;
    }

    void setLevel(const std::string& level) {
        level_ = level;
        std::cout << "[LOG] Level set to: " << level_ << std::endl;
    }

    std::string getLevel() const { return level_; }

private:
    Logger() : level_("INFO") {
        std::cout << "Logger instance created" << std::endl;
    }
    ~Logger() = default;

    std::string level_;
};

int main() {
    std::cout << "=== Singleton Demo ===" << std::endl;

    Logger& logger1 = Logger::getInstance();
    logger1.log("First message");
    logger1.setLevel("DEBUG");

    Logger& logger2 = Logger::getInstance();
    logger2.log("Second message");

    std::cout << "Same instance? " << (&logger1 == &logger2 ? "YES" : "NO") << std::endl;
    std::cout << "Level from logger2: " << logger2.getLevel() << std::endl;

    Logger::getInstance().log("Third message");
    Logger::getInstance().log("Singleton pattern ensures one instance");

    std::cout << "=== End Singleton Demo ===" << std::endl;
    return 0;
}
