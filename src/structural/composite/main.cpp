/**
 * Composite — 组合模式
 * ======================
 * 意图: 将对象组合成树形结构以表示"部分-整体"的层次结构。
 *       Composite 使得客户端对单个对象和组合对象的使用具有一致性。
 *
 * 练习要点:
 *   - Component 抽象基类 (统一 Leaf 和 Composite 的接口)
 *   - Leaf (叶子节点 — 无子节点)
 *   - Composite (组合节点 — 持有子节点列表)
 *   - 客户端不区分 Leaf 和 Composite
 *
 * 参考角色:
 *   Component (FileSystemNode) ← Leaf (File), Composite (Folder)
 */

#include <iostream>
#include <memory>
#include <string>
#include <vector>

// ============================================
// 评测检查清单 (Evaluation Checklist)
// ============================================
// 完成本模式后，你的实现应该展示：
//
// 结构要求 (必须包含以下类/接口):
//   ✓ Component 抽象基类
//   ✓ Leaf 叶子节点
//   ✓ Composite 组合节点 (含子节点列表)
//
// 行为要求 (运行时输出应展示):
//   ✓ 展示树形结构
//   ✓ 展示统一处理 Leaf 和 Composite
//   ✓ 展示递归操作
//
// 输出要求:
//   ✓ 输出应包含模式名称: "=== {Pattern} Demo ==="
//   ✓ 输出至少 5 行非空内容
//   ✓ 输出不应包含 "TODO"
//
// 参考实现: .reference/{pattern_name}.cpp
// 评测命令: python3 scripts/evaluate.py build src
// ============================================

// TODO: 实现你的 Composite

int main() {
    std::cout << "=== Composite Demo ===\n";
    // TODO
}
