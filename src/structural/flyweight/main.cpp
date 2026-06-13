/**
 * Flyweight — 享元模式
 * ======================
 * 意图: 运用共享技术有效地支持大量细粒度的对象。
 *
 * 练习要点:
 *   - 分离 intrinsic state (可共享) 和 extrinsic state (不可共享)
 *   - FlyweightFactory 管理共享对象池 (map)，确保同一 key 只创建一次
 *   - 客户端持有 extrinsic state，调用 flyweight->operation(extrinsicState)
 *   - 适用场景: 大量相似对象 (字符、粒子、缓存)
 *
 * C++23 可选特性:
 *   - std::flat_map / std::flat_set 替代 std::unordered_map (缓存友好)
 *   - std::assume_aligned 提示内存对齐，优化批量访问
 *   - std::expected 处理 getFlyweight() 不存在的 key
 *   - std::print / std::println 格式化输出池大小
 *   - std::shared_ptr 共享所有权 (intrinsic 数据设为 const)
 *
 * 参考角色:
 *   Flyweight (Glyph) ← ConcreteFlyweight (Character)
 *   FlyweightFactory (GlyphFactory)
 *   Context — 持有外在状态
 */

#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>

// ============================================
// 评测检查清单 (Evaluation Checklist)
// ============================================
// 完成本模式后，你的实现应该展示：
//
// 结构要求 (必须包含以下类/接口):
//   ✓ Flyweight 类 (含 intrinsic state)
//   ✓ FlyweightFactory (管理共享对象)
//   ✓ Client 使用 extrinsic state
//
// 行为要求 (运行时输出应展示):
//   ✓ 展示共享对象减少内存
//   ✓ 展示 intrinsic state 共享
//   ✓ 展示 extrinsic state 外部传入
//
// 输出要求:
//   ✓ 输出应包含模式名称: "=== {Pattern} Demo ==="
//   ✓ 输出至少 5 行非空内容
//   ✓ 输出不应包含 "TODO"
//
// 参考实现: .reference/{pattern_name}.cpp
// 评测命令: python3 scripts/evaluate.py build src
// ============================================

// TODO: 实现你的 Flyweight

int main() {
    std::cout << "=== Flyweight Demo ===\n";
    // TODO
}
