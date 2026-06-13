# Design Patterns in C++ — 完整设计模式学习项目

面向**深入学习**的 C++23 设计模式实验室：每一个子目录都是一个**自包含的 demo**，包含一个 `main.cpp`，
可独立编译运行，输出展示模式的核心结构、参与者交互及适用场景。

> 设计模式思想优先，C++23 特性作为增强表达力的辅助工具。手册中标注 C++23 增强的部分，
> 若编译器暂不支持，可用括号内的 C++20/C++17 替代方案。

## 快速开始

要求：支持 C++23 的编译器（GCC 13+、Clang 17+、MSVC 2022 17.8+）。

```bash
cd design-patterns-cpp
cmake -B build && cmake --build build

# 运行任意一个 demo
./build/singleton
./build/observer
./build/strategy
```

> 若编译器暂不支持 C++23，可将 `CMakeLists.txt` 中 `CMAKE_CXX_STANDARD` 改为 `20` 或 `17`，并忽略模板中 C++23 特有特性。

## 设计模式地图（GoF 23）

| 分类 | 模式 | 一句话 |
|---|---|---|
| **创建型** | Singleton | 全局唯一实例 |
| | Factory Method | 子类决定创建哪个对象 |
| | Abstract Factory | 创建一族相关对象 |
| | Builder | 分步骤构建复杂对象 |
| | Prototype | 克隆已有对象 |
| **结构型** | Adapter | 转换接口以兼容 |
| | Bridge | 分离抽象与实现 |
| | Composite | 树形结构的统一处理 |
| | Decorator | 动态添加职责 |
| | Facade | 简化复杂子系统的接口 |
| | Flyweight | 共享细粒度对象 |
| | Proxy | 控制对象访问 |
| **行为型** | Chain of Resp. | 请求沿链传递 |
| | Command | 将请求封装为对象 |
| | Interpreter | 解释自定义语言 |
| | Iterator | 顺序访问集合元素 |
| | Mediator | 集中协调对象交互 |
| | Memento | 捕获并恢复对象状态 |
| | Observer | 一对多的依赖通知 |
| | State | 状态驱动的行为变化 |
| | Strategy | 算法族，可互换 |
| | Template Method | 定义算法骨架，子类填充步骤 |
| | Visitor | 对一组对象执行新操作 |

## 学习路线建议

1. **第一轮** — 创建型 → 结构型 → 行为型，顺序通读
2. **第二轮** — 对比相似模式：Strategy vs State、Decorator vs Proxy、Factory Method vs Abstract Factory
3. **第三轮** — 组合使用：在一个场景里混合多个模式
4. **第四轮** — 回归你工作中的代码，识别可应用模式的地方
