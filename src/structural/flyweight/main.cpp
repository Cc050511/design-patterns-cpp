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

// TODO: 实现你的 Flyweight

int main() {
    std::cout << "=== Flyweight Demo ===\n";
    // TODO
}
