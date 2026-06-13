/**
 * Singleton — 全局唯一实例，禁止拷贝，延迟初始化
 * 意图: 全局唯一实例，禁止拷贝，延迟初始化
 * 评测: python3 scripts/evaluate.py build src
 * 参考: .reference/singleton.cpp
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

