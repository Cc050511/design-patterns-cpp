# 评测系统说明

本项目采用 **四层综合评测** 确保每个设计模式实现符合 GoF 标准：

## 1. 编译期验证 (Build)
- **CMake 构建**: 所有 23 个 demo 可执行文件必须编译通过
- **clang-tidy 静态检查**: 检查现代 C++ 实践
- **二进制存在检查**: 每个模式必须生成对应二进制文件

## 2. 结构期验证 (Structure)
- **脚本**: `scripts/verify_structure.sh`
- **检查内容**: 每个 `main.cpp` 中是否包含该模式的关键角色/术语
  - 例如 Singleton 需包含 `Singleton|instance|delete|copy` 等关键词
  - 基于 `grep -iE` 正则匹配，检查注释和实现代码

## 3. 运行时验证 (Runtime)
- **脚本**: `scripts/verify_runtime.sh`
- **检查内容**:
  1. 程序运行不崩溃 (exit 0)
  2. 输出包含模式名称
  3. 输出 **不包含** `TODO` (说明已实现完整交互)
  4. 输出至少 3 行非空内容

## 4. 评测引擎 (Evaluation Engine)
- **脚本**: `scripts/evaluate.py`
- **功能**: 综合评分系统，为每个模式给出 0-100 分
- **评分维度**:
  - 编译通过 (25分)
  - 运行不崩溃 (25分)
  - 输出内容正确 (25分): 包含模式名称、无 TODO、至少 3 行
  - 结构正确 (25分): 包含模式关键角色/术语
  - 参考对比 (加分项): 与 `.reference/` 下的参考实现对比行为

## 5. 行为测试 (Behavior Tests)
- **框架**: Catch2 v3
- **测试目录**: `tests/`
- **测试内容**:
  - `all_patterns_test`: 检查所有二进制存在 + 运行输出检查
  - 更多深度测试可扩展

## 本地运行完整评测

```bash
cd design-patterns-cpp
cmake -B build && cmake --build build

# 1. 结构验证
bash scripts/verify_structure.sh src

# 2. 运行时验证
bash scripts/verify_runtime.sh build

# 3. 综合评测 (推荐)
python3 scripts/evaluate.py build src

# 4. 行为测试
cd build && ctest --output-on-failure
```

## 评测标准

每个模式通过需要 >= 75/100 分:

| 检查项 | 分值 | 说明 |
|--------|------|------|
| 编译通过 | 25分 | C++23 编译无错误 |
| 运行正常 | 25分 | 程序不崩溃 |
| 输出内容 | 25分 | 包含模式名称、无 TODO、≥3行 |
| 结构正确 | 25分 | 包含 GoF 定义的关键角色 |
| 参考对比 | +10分 | 行为与参考实现一致 (加分项) |

## 参考实现

`.reference/` 目录下存放每个模式的**参考实现**，供用户对比学习。
这些参考实现:
- 是完整的、可编译的 C++23 程序
- 正确展示了设计模式的核心行为
- 可以作为"黄金标准"来对比自己的实现

## 为用户完成 demo 后评测

当用户完成一个 demo 的实现后，评测标准如下:

1. **编译**: 无错误
2. **结构**: 包含模式关键角色类/函数
3. **运行时**: 输出 ≥3 行，展示核心交互
4. **行为**: 符合 GoF 设计模式定义

**当前状态**: 所有 demo 为空模板（仅 TODO），运行时验证和评测引擎预期为部分失败状态。完成实现后应全部通过。

