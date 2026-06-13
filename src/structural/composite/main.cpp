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

// TODO: 实现你的 Composite

int main() {
    std::cout << "=== Composite Demo ===\n";
    // TODO
}
