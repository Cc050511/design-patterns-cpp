#include <iostream>

/**
 * Singleton — 单例模式
 * 意图: 全局唯一实例，禁止拷贝，延迟初始化
 * 评测: python3 scripts/evaluate.py build src
 * 参考: .reference/singleton.cpp
 */

class Singleton {
  public:
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;
    Singleton(Singleton&&) = delete;
    Singleton& operator=(Singleton&&) = delete;

    static Singleton& instance() {
        static Singleton instance;
        return instance;
    }

    void operation() const {
        std::cout << "Singleton instance address: " << this << "\n";
    }

  private:
    Singleton() {
        std::cout << "Singleton constructed (lazy init)\n";
    }
    ~Singleton() = default;
};

int main() {
    std::cout << "=== Singleton Demo ===\n";
    std::cout << "Getting instance 1...\n";
    Singleton& s1 = Singleton::instance();
    s1.operation();

    std::cout << "Getting instance 2...\n";
    Singleton& s2 = Singleton::instance();
    s2.operation();

    std::cout << "Same instance? " << (&s1 == &s2 ? "YES" : "NO") << "\n";
    std::cout << "Singleton verified successfully.\n";
    return 0;
}
