/**
 * Singleton — 单例模式
 * ======================
 * 意图: 确保一个类只有一个实例，并提供一个全局访问点。
 *
 * 练习要点:
 *   - C++11 局部静态变量 (Meyer's Singleton) 的线程安全性 (§6.7.4)
 *   - 禁止拷贝/移动构造
 *   - [可选] 实现懒汉式 + double-checked locking
 *
 * 参考角色:
 *   Singleton — 自身管理唯一实例
 */

// ============================================
// 评测检查清单 (Evaluation Checklist)
// ============================================
// 完成本模式后，你的实现应该展示：
//
// 结构要求 (必须包含以下类/接口):
//   ✓ Singleton 类 (禁止外部构造)
//   ✓ instance() 静态方法 (返回唯一实例)
//   ✓ 禁止拷贝/移动 (= delete 或 private)
//
// 行为要求 (运行时输出应展示):
//   ✓ 多次调用 instance() 返回同一实例
//   ✓ 展示实例地址相同
//   ✓ 展示延迟初始化 (lazy init)
//
// 输出要求:
//   ✓ 输出应包含模式名称: "=== Singleton Demo ==="
//   ✓ 输出至少 5 行非空内容
//   ✓ 输出不应包含 "TODO"
//
// 参考实现: .reference/singleton.cpp
// 评测命令: python3 scripts/evaluate.py build src
// ============================================

#include <iostream>

class Singleton {
  public:
    static Singleton& instance() {
        static Singleton instance;
        return instance;
    }

    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;
    Singleton(Singleton&&) = delete;
    Singleton& operator=(Singleton&&) = delete;

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
