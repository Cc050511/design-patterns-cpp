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

// ============================================
// 评测检查清单 (Evaluation Checklist)
// ============================================
// 完成本模式后，你的实现应该展示：
//
// 结构要求 (必须包含以下类/接口):
//   ✓ Subject 接口
//   ✓ RealSubject 真实对象
//   ✓ Proxy 代理类 (控制访问)
//
// 行为要求 (运行时输出应展示):
//   ✓ 展示 Proxy 控制访问
//   ✓ 展示延迟创建 RealSubject
//   ✓ 展示访问前后的额外操作
//
// 输出要求:
//   ✓ 输出应包含模式名称: "=== {Pattern} Demo ==="
//   ✓ 输出至少 5 行非空内容
//   ✓ 输出不应包含 "TODO"
//
// 参考实现: .reference/{pattern_name}.cpp
// 评测命令: python3 scripts/evaluate.py build src
// ============================================

// TODO: 实现你的 Proxy

int main() {
    std::cout << "=== Proxy Demo ===\n";
    // TODO
}
