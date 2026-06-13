/**
 * Singleton — 全局唯一实例，禁止拷贝，延迟初始化
 *
 * 核心结构：一个类，全局唯一实例，禁止拷贝/构造，提供静态访问方法
 * 评测要点：
 *   - 结构：class Singleton, static instance(), delete copy, private constructor
 *   - 行为：获取实例、验证地址相同、展示延迟初始化
 *   - 输出：包含 "Singleton"、"instance"、"same"、"construct" 等关键词
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

