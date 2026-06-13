# 评测系统文档

## 概述

本项目为 GoF 23 种设计模式提供完整的评测系统，帮助用户验证自己的实现是否符合设计模式的行为和结构要求。

## 评测体系

### 四层验证

1. **编译验证** (10分): 检查代码是否能通过 C++23 编译
2. **结构验证** (25分): 检查代码是否包含 GoF 定义的关键角色（类、方法、关系）
3. **行为验证** (45分): 运行时验证设计模式的核心行为（最重要）
4. **参考对比** (10分): 与 `.reference/` 下的参考答案进行输出对比

**通过标准：75分/100分**

## 文件结构

```
scripts/
  ├── evaluate.py              # 主评测引擎
  ├── evaluation_criteria.json   # 评分标准
  ├── verify_structure.sh      # 结构验证脚本
  ├── verify_runtime.sh        # 运行时验证脚本
  └── README.md                # 评测系统说明

.reference/
  ├── singleton.cpp            # 参考答案
  ├── factory_method.cpp
  ├── ... (共 23 个)
  └── visitor.cpp
```

## 评分标准

### 每个模式的评分维度

| 维度 | 分值 | 说明 |
|------|------|------|
| 编译成功 | 10分 | 代码必须能通过 C++23 编译 |
| 结构正确 | 25分 | 包含 GoF 定义的关键角色（正则匹配） |
| 行为正确 | 45分 | 运行时展示设计模式核心行为（关键词匹配） |
| 输出质量 | 10分 | 输出包含模式名称、无 TODO、至少 5 行 |
| 参考对比 | 10分 | 与参考答案的行为输出相似度 |

### 评分示例

**正确实现（Singleton）：**

```
[PASS] Compilation (+10)
[PASS] Structure: Singleton类定义 (+6.2)
[PASS] Structure: 静态实例访问方法 (+6.2)
[PASS] Structure: 禁止外部构造 (+6.2)
[PASS] Structure: 禁止拷贝 (+6.2)
[PASS] Runtime execution
[PASS] Behavior: 展示实例获取 (+15.0)
[PASS] Behavior: 展示同一实例地址 (+15.0)
[PASS] Behavior: 展示延迟初始化 (+15.0)
[PASS] Output: 8 lines (>= 5)
[FAIL] Reference: 20% similarity (0)
Score: 90.0/100
```

**空模板（未实现）：**

```
[PASS] Compilation (+10)
[FAIL] Structure: Singleton类定义 (missing)
[FAIL] Structure: 静态实例访问方法 (missing)
[FAIL] Structure: 禁止外部构造 (missing)
[FAIL] Structure: 禁止拷贝 (missing)
[PASS] Runtime execution
[FAIL] Behavior: 展示实例获取 (missing in output)
[FAIL] Behavior: 展示同一实例地址 (missing in output)
[FAIL] Behavior: 展示延迟初始化 (missing in output)
[FAIL] Output: 1 lines (< 5)
Score: 10.0/100
```

## 使用方法

### 基本评测

```bash
# 1. 编译项目
cmake -B build && cmake --build build

# 2. 运行评测引擎
python3 scripts/evaluate.py build src
```

### 生成评测报告

```bash
# 评测完成后自动生成 evaluation_report.md
python3 scripts/evaluate.py build src
cat evaluation_report.md
```

### 单独评测某个模式

```bash
# 运行特定模式的可执行文件
./build/singleton

# 查看该模式的详细评分
python3 scripts/evaluate.py build src | grep -A 15 "Singleton"
```

## 参考答案

### 什么是参考答案

`.reference/` 目录下存放了 23 个模式的**完整参考实现**。
这些实现：
- 是正确的 GoF 设计模式实现
- 展示完整的行为和输出
- 可以作为实现范例

### 如何使用参考答案

```bash
# 编译参考实现
g++ -std=c++23 .reference/singleton.cpp -o singleton_ref

# 运行参考实现
./singleton_ref

# 对比自己的实现
./build/singleton
```

## 评测流程

### 完整评测流程

```bash
# 1. 编译
cmake -B build && cmake --build build

# 2. 结构验证
bash scripts/verify_structure.sh src

# 3. 运行时验证
bash scripts/verify_runtime.sh build

# 4. 综合评测
python3 scripts/evaluate.py build src

# 5. 查看报告
cat evaluation_report.md
```

### CI 自动评测

GitHub Actions 自动执行：
1. 编译所有 demo
2. 运行结构验证
3. 运行评测引擎
4. 生成评分报告

在 PR 页面查看评测结果。

## 评分标准详解

### 结构验证 (25分)

检查代码中是否包含 GoF 定义的关键角色：

| 模式 | 检查项 | 描述 |
|------|--------|------|
| Singleton | `class Singleton` | Singleton类定义 |
| Singleton | `static.*instance` | 静态实例访问方法 |
| Singleton | `delete|private.*Singleton|constructor` | 禁止外部构造 |
| Singleton | `delete.*copy|delete|copy` | 禁止拷贝 |
| Observer | `class Subject` | Subject类 |
| Observer | `class Observer` | Observer类 |
| Observer | `attach|subscribe|register` | 注册方法 |
| Observer | `notify|update|push` | 通知方法 |
| ... | ... | ... |

### 行为验证 (45分)

检查运行时输出是否展示设计模式的核心行为：

| 模式 | 检查项 | 描述 |
|------|--------|------|
| Singleton | `instance` | 展示实例获取 |
| Singleton | `address|same|identical|equal` | 展示同一实例地址 |
| Singleton | `construct|init|lazy` | 展示延迟初始化 |
| Observer | `attach|subscribe|register` | 展示注册观察者 |
| Observer | `state|change|update` | 展示状态变化 |
| Observer | `notify|update|push` | 展示通知更新 |
| Observer | `multiple|many|all` | 展示一对多通知 |
| ... | ... | ... |

### 输出质量 (10分)

- 输出至少 5 行非空内容 (5分)
- 包含模式名称（如 `Singleton Demo`）(3分)
- 不包含 `TODO` 关键词 (2分)

### 参考对比 (10分)

- 与参考答案的输出相似度 ≥ 50%：+10分
- 相似度 ≥ 30%：+5分
- 相似度 < 30%：0分

## 常见问题

### 为什么编译通过了但分数很低？

编译通过只获得 10 分。评测系统主要检查：
1. **结构**：是否包含正确的类和方法（25分）
2. **行为**：运行时是否展示核心行为（45分）
3. **输出质量**：输出是否清晰、完整（10分）

### 如何提高分数？

1. **实现完整的设计模式**：包含所有关键角色（类、接口）
2. **展示运行时行为**：输出应该展示设计模式的核心交互
3. **参考参考答案**：对比 `.reference/` 下的实现，确保输出格式相似

### 评测引擎如何判断行为是否正确？

通过分析运行时输出，检查是否包含预定义的行为关键词。
例如 Singleton 需要展示：
- 实例获取
- 同一实例地址
- 延迟初始化

## 扩展评测系统

### 添加新的评测标准

编辑 `scripts/evaluation_criteria.json`：

```json
{
  "patterns": {
    "singleton": {
      "scores": {
        "compilation": 10,
        "structure": 25,
        "behavior": 45,
        "output_quality": 10,
        "reference": 10
      },
      "structure_checks": {
        "must_have": [
          {"pattern": "class Singleton", "description": "Singleton类定义"},
          {"pattern": "static.*instance", "description": "静态实例访问方法"}
        ]
      },
      "behavior_checks": {
        "must_have": [
          {"keyword": "instance", "description": "展示实例获取"}
        ]
      }
    }
  }
}
```

### 自定义评分权重

修改 `evaluation_criteria.json` 中的 `scores` 字段：

```json
"scores": {
  "compilation": 10,
  "structure": 25,
  "behavior": 45,
  "output_quality": 10,
  "reference": 10
}
```

## 技术细节

### 评测引擎实现

- **语言**：Python 3
- **核心逻辑**：
  1. 编译检查：检查二进制文件是否存在
  2. 结构检查：正则匹配代码中的关键角色
  3. 行为检查：运行时输出关键词匹配
  4. 参考对比：文本相似度计算

### 正则匹配

结构检查使用正则表达式匹配代码：
```python
re.search(r"class\s+\w*Singleton", content, re.IGNORECASE)
```

### 行为匹配

行为检查使用关键词匹配：
```python
"instance".lower() in output.lower()
```

## 总结

评测系统提供：
1. **客观评分**：基于运行时行为的量化评分
2. **详细反馈**：每项检查都有具体的通过/失败说明
3. **参考对比**：与参考答案对比，帮助改进实现
4. **自动化**：本地运行和 CI 集成

通过评测系统，用户可以快速验证自己的设计模式实现是否符合 GoF 标准，并获得改进建议。
