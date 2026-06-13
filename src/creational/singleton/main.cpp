/**
 * Singleton — 全局唯一实例，禁止拷贝，延迟初始化
 *
 * 实现要求：
 * 1. 设计并实现此设计模式的完整结构
 * 2. 在 main() 中演示该模式的核心交互
 * 3. 输出需包含模式名称，展示关键行为
 *
 * 评测：python3 scripts/evaluate.py build src
 * 参考：.reference/singleton.cpp
 */

#include <iostream>

// TODO: 完成以下类实现

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
    Singleton& s1 = Singleton::instance();
    s1.operation();
    Singleton& s2 = Singleton::instance();
    s2.operation();
    std::cout << "Same instance? " << (&s1 == &s2 ? "YES" : "NO") << "\n";
    std::cout << "Singleton verified successfully.\n";
    return 0;
}

