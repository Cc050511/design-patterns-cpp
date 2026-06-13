/**
 * Proxy — 代理模式
 * ==================
 * 意图: 为其他对象提供一种代理以控制对这个对象的访问。
 *
 * 练习要点:
 *   - Subject 抽象接口 (定义 RealSubject 和 Proxy 的共同接口)
 *   - RealSubject 是真正干活的对象 (开销大/受保护的资源)
 *   - Proxy 持有 RealSubject* 或引用
 *   - 四种常见变体:
 *       1. Virtual Proxy  — 延迟创建 (本例推荐)
 *       2. Protection Proxy — 访问控制
 *       3. Remote Proxy    — 代表远程对象
 *       4. Logging Proxy   — 日志/缓存
 *
 * 参考角色:
 *   Subject (Image) ← RealSubject (RealImage), Proxy (LazyImageProxy)
 */

#include <iostream>
#include <memory>
#include <string>

// TODO: 实现你的 Proxy

int main() {
    std::cout << "=== Proxy Demo ===\n";
    // TODO
}
