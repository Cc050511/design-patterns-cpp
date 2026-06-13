# 设计模式详解 — C++ 参考手册

> 面向 GoF 23 种设计模式的完整学习参考。基于 **C++23** 标准编写，与 `/src/` 下的实现模板配合使用。
> 
> 主次分明：设计模式思想优先，C++23 特性作为增强表达力的辅助工具。

## 目录

创建型: [Singleton](#1-singleton--单例模式) · [Factory Method](#2-factory-method--工厂方法模式) · [Abstract Factory](#3-abstract-factory--抽象工厂模式) · [Builder](#4-builder--建造者模式) · [Prototype](#5-prototype--原型模式)

结构型: [Adapter](#6-adapter--适配器模式) · [Bridge](#7-bridge--桥接模式) · [Composite](#8-composite--组合模式) · [Decorator](#9-decorator--装饰器模式) · [Facade](#10-facade--外观模式) · [Flyweight](#11-flyweight--享元模式) · [Proxy](#12-proxy--代理模式)

行为型: [Chain of Resp.](#13-chain-of-responsibility--职责链模式) · [Command](#14-command--命令模式) · [Interpreter](#15-interpreter--解释器模式) · [Iterator](#16-iterator--迭代器模式) · [Mediator](#17-mediator--中介者模式) · [Memento](#18-memento--备忘录模式) · [Observer](#19-observer--观察者模式) · [State](#20-state--状态模式) · [Strategy](#21-strategy--策略模式) · [Template Method](#22-template-method--模板方法模式) · [Visitor](#23-visitor--访问者模式)

附录: [设计原则](#a-设计原则速查) · [模式对比](#b-模式对比表) · [C++ 要点](#c-c-实现要点)

---

## 1. Singleton — 单例模式

### 意图
确保一个类只有一个实例，并提供一个全局访问点。

### 动机
一些情况下系统中只需一个对象实例：日志模块、配置管理、线程池、数据库连接池。全局变量可以做到"全局访问"，但无法阻止你创建多个对象。Singleton 把"单例"这个约束编码到类本身。

### 结构（Meyer's Singleton 实现）

```
┌──────────────────────┐
│      Singleton       │
├──────────────────────┤
│ - Singleton()        │  ← 构造为 private
│ - ~Singleton()       │
│ - Singleton(const&)  │  ← 拷贝/移动 delete
│ + instance() → S&    │  ← 静态方法，内部 local static
│ + operation()        │
└──────────────────────┘
```

### C++ 实现要点
1. **Meyer's Singleton**（推荐）: 函数内 `static` 局部变量由 C++11 §6.7.4 保证线程安全初始化
2. **禁止拷贝和移动**: `= delete` 拷贝构造、移动构造、赋值运算符
3. **懒汉式 + DCL**: 使用 `std::atomic` + `std::mutex`，C++11 起 `atomic` 保证内存顺序
4. **饿汉式**: `static` 成员在 `main()` 前初始化，线程安全但可能浪费资源

### 优缺点
| 优点 | 缺点 |
|------|------|
| 严格控制唯一实例 | 引入全局状态，增加耦合 |
| 延迟初始化（Meyer's） | 难以单元测试（无法 mock） |
| 比全局变量更安全 | 多线程下需谨慎处理 |

### 何时使用
- 系统中确实只需要一个实例（日志、配置、硬件接口抽象）
- 需要比全局变量更强的约束条件

---

## 2. Factory Method — 工厂方法模式

### 意图
定义一个用于创建对象的接口，让子类决定实例化哪个类。工厂方法使一个类的实例化延迟到其子类。

### 动机
当类 A 需要创建对象 B，但 A 不知道应该创建 B 的哪个具体子类时，可以让 A 的子类来决定。这样 A 的代码只依赖 B 的抽象接口，符合依赖倒置原则。

### 结构

```
┌─────────────┐         ┌─────────────┐
│   Creator   │────────→│   Product   │
├─────────────┤         ├─────────────┤
│ + factory() │         │ + operation │
│ + doStuff() │         └─────────────┘
└──────┬──────┘                △
       │                       │
┌──────┴──────┐         ┌─────┴──────┐
│ConcreteCr.  │         │ConcreteProd│
│ + factory() │         │ + operation│
└─────────────┘         └────────────┘
```

### C++ 实现要点
1. **Creator 可以是抽象类或具体类**：工厂方法可以是纯虚的，也可以提供默认实现
2. **返回 `std::unique_ptr<Product>`** 表达所有权转移，避免内存泄漏
3. **参数化工厂方法**：工厂方法可以接收参数（如类型标识），内部用 switch 创建不同对象
4. **与 Template Method 的关系**：工厂方法常作为模板方法中的一个步骤（如文档创建中的 `createPage()`）

### 优缺点
| 优点 | 缺点 |
|------|------|
| 解耦产品创建与使用 | 每增加一个产品就要增加一个子类 |
| 符合开闭原则 | 类数量膨胀 |
| 子类可定制创建逻辑 | 简单场景可能过度设计 |

### 何时使用
- 类不知道它所需对象的确切类型
- 类希望由子类来指定创建的对象
- 需要解耦对象的创建逻辑和使用逻辑

---

## 3. Abstract Factory — 抽象工厂模式

### 意图
提供一个创建一系列相关或相互依赖对象的接口，而无需指定它们的具体类。

### 动机
当你需要创建一组配套的产品（如 UI 套件中的 Button + Checkbox + Scrollbar），且这些产品有多种风格（Win/Mac/Linux），抽象工厂确保同一族的产品总是配套使用。

### 结构

```
┌─────────────────┐     ┌─────────────┐     ┌─────────────┐
│ AbstractFactory │     │ProductA_IF  │     │ProductB_IF  │
├─────────────────┤     ├─────────────┤     ├─────────────┤
│ + createA()     │     │ + doA()     │     │ + doB()     │
│ + createB()     │     └──────┬──────┘     └──────┬──────┘
└────────┬────────┘            │                    │
         │                     │                    │
┌────────┴────────┐     ┌─────┴─────┐       ┌─────┴─────┐
│ ConcreteFactory │     │ConcreteA1 │       │ConcreteB1 │
│ + createA()     │     │ + doA()   │       │ + doB()   │
│ + createB()     │     └───────────┘       └───────────┘
└─────────────────┘
```

### C++ 实现要点
1. **一族产品 = 多个工厂方法**：每个 `createX()` 返回一个抽象产品接口
2. **工厂本身可以是 Singleton**：系统中通常只需要一个具体工厂实例
3. **使用 `std::unique_ptr` 返回产品**：清晰的所有权语义
4. **与 Factory Method 的区别**：抽象工厂创建一族相关产品；工厂方法创建单个产品

### 优缺点
| 优点 | 缺点 |
|------|------|
| 确保产品族一致性 | 新增产品类型需要修改所有工厂接口 |
| 隔离具体类的使用 | 类数量较多 |
| 易于切换整个产品族 | 复杂度高于 Factory Method |

### 何时使用
- 需要创建相互关联/依赖的对象族
- 系统需要独立于产品的创建、组合和表示
- 需要提供一个产品类库，只想暴露接口不暴露实现

---

## 4. Builder — 建造者模式

### 意图
将一个复杂对象的构建与它的表示分离，使得同样的构建过程可以创建不同的表示。

### 动机
当一个对象由多个部分组成，且构建顺序和细节复杂时（如 SQL 查询、HTTP 请求、游戏角色），把构建步骤抽出来，让不同的建造者实现不同的细节。

### 结构

```
┌─────────────┐      ┌─────────────┐      ┌─────────────┐
│  Director   │──────│   Builder   │      │   Product   │
├─────────────┤      ├─────────────┤      ├─────────────┤
│ construct() │      │ buildA()    │      │ (复杂对象)  │
│             │      │ buildB()    │      └─────────────┘
└─────────────┘      │ getResult() │
                     └──────┬──────┘
                            │
                     ┌──────┴──────┐
                     │ConcreteBuilder│
                     │ buildA()    │
                     │ buildB()    │
                     └─────────────┘
```

### C++ 实现要点
1. **Director 可选**：如果构建顺序固定，可以封装；如果顺序灵活，客户端可直接调用 Builder
2. **Builder 方法返回 `Builder&` 或 `*this`**：支持链式调用（fluent interface）
3. **与 Factory Method 的区别**：Builder 关注分步骤构建复杂对象；Factory 关注创建单一对象
4. **C++23 增强**：
   - **显式对象参数** (`this T&&`)：Builder 方法可用 `auto build(this auto&& self)` 实现完美转发，省 4 份重载
   - **`std::optional` monadic 操作**：`opt.and_then(...).or_else(...)` 链式处理可选构建步骤
   - **`std::print` / `std::println`**：输出构建日志时类型安全、格式化
   - **`std::flat_map`**：管理 Builder 的默认配置项，缓存友好
5. **C++20 仍可用**：`std::optional` 处理可选步骤，`std::move` 转移构建结果

### 优缺点
| 优点 | 缺点 |
|------|------|
| 构建过程精细控制 | 类数量增加 |
| 同一过程可产生不同表示 | 需要创建 Director 和 Builder |
| 隐藏产品内部结构 | 简单对象不需要 Builder |
| 支持链式调用 | |

### 何时使用
- 创建复杂对象，需要分步骤构建
- 对象的构建过程应该独立于组成部分
- 需要支持多种不同表示（如 HTML vs Plain Text 简历）

---

## 5. Prototype — 原型模式

### 意图
用原型实例指定创建对象的种类，并且通过拷贝这些原型创建新的对象。

### 动机
当对象的创建成本高昂（需要数据库查询、复杂计算），或对象的类在运行时才能确定时，与其用 new 创建，不如复制一个已有的实例。

### 结构

```
┌─────────────────┐
│   Prototype     │
├─────────────────┤
│ + clone() → P*  │
└───────┬─────────┘
        │
┌───────┴─────────┐
│ConcretePrototype│
│ + clone()       │
└─────────────────┘
```

### C++ 实现要点
1. **虚 `clone()` 方法**：基类声明 `virtual Prototype* clone() const = 0`，子类用拷贝构造函数实现
2. **深拷贝 vs 浅拷贝**：如果 Prototype 包含指针成员，必须实现深拷贝（或禁用默认拷贝）
3. **Prototype Registry**：用一个 `std::unordered_map<std::string, std::unique_ptr<Prototype>>` 管理原型对象，客户端通过 key 获取 clone
4. **C++23 增强**：
   - **`std::clone_ptr` / `std::cloneable`**：若编译器支持，可直接用 `std::clone_ptr<Prototype>` 管理原型，省手写虚 `clone()` 和 `std::unique_ptr` 的 boilerplate
   - **`std::flat_map`**：管理原型注册表，缓存友好，比 `std::unordered_map` 更紧凑
5. **C++20 仍可用**：`clone()` 返回 `std::unique_ptr<Prototype>` 更安全

### 优缺点
| 优点 | 缺点 |
|------|------|
| 避免子类爆炸 | 每个类都需要实现 clone |
| 运行时确定对象类型 | 深拷贝可能复杂且危险 |
| 隐藏复杂创建逻辑 | |

### 何时使用
- 创建对象的成本显著高于复制
- 需要避免与产品类层次平行的工厂类层次
- 实例的状态只有少量组合，可以预置原型

---

## 6. Adapter — 适配器模式

### 意图
将一个类的接口转换成客户希望的另一个接口。Adapter 使得原本由于接口不兼容而不能一起工作的类可以一起工作。

### 动机
已有成熟类库（如第三方 API、旧代码），但接口不兼容新系统。与其修改原有代码，不如封装一个适配层。

### 结构

**对象适配器（组合）**
```
┌──────────┐         ┌──────────┐        ┌──────────┐
│  Client  │────────→│  Target  │        │  Adaptee │
│          │         │ + request│        │+specific │
└──────────┘         └────┬─────┘        └────┬─────┘
                          │                   │
                    ┌─────┴─────┐             │
                    │  Adapter  │─────────────┘
                    │ + request │   (组合 Adaptee)
                    └───────────┘
```

**类适配器（多重继承）**
```
                    ┌──────────┐
                    │  Target  │
                    │ + request│
                    └────┬─────┘
                         │
              ┌──────────┴──────────┐
              │      Adapter        │
              │ + request()         │
              │   (调用 Adaptee::specific())
              └──────────┬──────────┘
                         │
                    ┌────┴─────┐
                    │  Adaptee │
                    │+specific │
                    └──────────┘
```

### C++ 实现要点
1. **对象适配器 vs 类适配器**：对象适配器（组合）更灵活，可以适配 Adaptee 的子类；类适配器（多重继承）在 C++ 中可行，但耦合更强
2. **C++ 推荐对象适配器**：使用 `std::unique_ptr<Adaptee>` 或引用持有被适配对象
3. **与 Decorator 的区别**：Adapter 改变接口；Decorator 保持接口并添加职责
4. **适配器也可以适配多个 Adaptee**：封装多个不兼容接口为统一 Target

### 优缺点
| 优点 | 缺点 |
|------|------|
| 复用现有类 | 额外的一层间接性 |
| 无需修改原有代码 | 类适配器可能引入菱形继承问题 |
| 目标与适配者解耦 | |

### 何时使用
- 想使用已有类，但其接口不符合需求
- 需要创建可复用的类，与接口不兼容的类协同工作
- 需要统一多个不同接口的类

---

## 7. Bridge — 桥接模式

### 意图
将抽象部分与它的实现部分分离，使它们都可以独立地变化。

### 动机
如果一个问题有两个维度变化（如图形形状 + 渲染方式），用继承会产生类爆炸（CircleWin, CircleMac, CircleLinux, RectangleWin...）。Bridge 用组合替代多层继承。

### 结构

```
┌─────────────┐              ┌─────────────┐
│ Abstraction │──────────────│Implementor  │
│ + operation │   (impl_)    │ + operation │
└──────┬──────┘              └──────┬──────┘
       │                         │
┌──────┴──────┐            ┌─────┴──────┐
│RefinedAbst. │            │ConcreteImpl│
│ + operation │            │ + operation│
└─────────────┘            └────────────┘
```

### C++ 实现要点
1. **关键：用组合替代继承**：`Abstraction` 持有 `Implementor*` 或 `std::unique_ptr<Implementor>`
2. **两者独立扩展**：新增 `Abstraction` 子类不改动 `Implementor` 体系，反之亦然
3. **与 Strategy 的区别**：Bridge 是两个层级结构共同完成一个概念；Strategy 是单一上下文替换算法
4. **C++ 实现技巧**：用 `std::unique_ptr<Implementor>` 管理实现，构造函数注入

### 优缺点
| 优点 | 缺点 |
|------|------|
| 抽象和实现独立扩展 | 增加设计的复杂度 |
| 避免类爆炸 | 对简单场景过度设计 |
| 隐藏实现细节 | |

### 何时使用
- 一个类存在两个独立变化的维度
- 需要用继承之外的方式扩展实现
- 需要在多个对象间共享实现

---

## 8. Composite — 组合模式

### 意图
将对象组合成树形结构以表示"部分-整体"的层次结构。Composite 使得客户端对单个对象和组合对象的使用具有一致性。

### 动机
当系统需要处理树形结构（如文件系统、UI 组件树、组织架构），且客户端不应区分叶子节点和组合节点时，Composite 提供统一接口。

### 结构

```
┌─────────────┐
│  Component  │
├─────────────┤
│ + operation │
│ + add(c)    │
│ + remove(c) │
│ + getChild()│
└──────┬──────┘
       │
   ┌───┴───┐
   │       │
┌──┴──┐ ┌──┴─────┐
│ Leaf│ │Composite│
│+op. │ │+op()    │
│     │ │  for c in children: c.operation()│
└─────┘ │children:│
        └─────────┘
```

### C++ 实现要点
1. **Component 统一接口**：`Leaf` 和 `Composite` 继承同一接口，客户端无需区分
2. **透明性 vs 安全性**：透明方式在 Component 中声明 `add/remove`（Leaf 实现为空或抛异常）；安全方式只在 Composite 中声明（客户端需要类型判断）
3. **C++ 实现技巧**：`children` 用 `std::vector<std::unique_ptr<Component>>` 管理；`operation()` 递归调用
4. **与 Decorator 的区别**：Composite 表示树形结构；Decorator 是递归添加职责

### 优缺点
| 优点 | 缺点 |
|------|------|
| 客户端无需区分叶子和组合 | 可能使设计过于一般化 |
| 易于新增组件类型 | 透明方式 Leaf 需实现无意义的方法 |
| 树形结构自然表达 | |

### 何时使用
- 需要表示对象的部分-整体层次结构
- 希望客户端忽略组合对象与单个对象的差异
- 需要递归处理树形结构

---

## 9. Decorator — 装饰器模式

### 意图
动态地给一个对象添加一些额外的职责。就增加功能来说，Decorator 模式比生成子类更为灵活。

### 动机
继承是静态扩展，运行期无法撤销。Decorator 允许在运行期叠加多个功能，且每个功能独立封装。

### 结构

```
┌─────────────┐
│  Component  │
│ + operation │
└──────┬──────┘
       │
   ┌───┴───────────┐
   │               │
┌──┴──────┐  ┌─────┴──────┐
│Concrete │  │  Decorator │
│Component│  │  (component│
│+op.    │  │   _ 引用)  │
└─────────┘  │ + operation│
             └─────┬──────┘
                   │
          ┌────────┴────────┐
          │ ConcreteDecoA   │
          │ + operation()   │
          │   (before/after)│
          └─────────────────┘
```

### C++ 实现要点
1. **Decorator 继承 Component 且持有 Component***：这是关键，使得装饰器可以嵌套（`new B(new A(new C()))`）
2. **透明性**：客户端看到的始终是 Component 接口，不知道是否被装饰
3. **C++23 增强**：
   - **显式对象参数** (`this T&&`)：Decorator 的 `operation()` 可用 `auto operation(this auto&& self)` 完美转发，省 4 份重载，保持 const-correctness
   - **`std::move_only_function`**：回调式装饰器可绑定只移不可拷的 lambda
   - **`std::println` 装饰日志**：`std::println("[Decorator] 执行前操作")` 类型安全输出
4. **C++20 仍可用**：`std::unique_ptr<Component>` 持有被装饰对象；构造函数注入
5. **与 Adapter 的区别**：Decorator 保持接口并添加职责；Adapter 改变接口
6. **与 Composite 的区别**：Decorator 只有一个子组件；Composite 有多个

### 优缺点
| 优点 | 缺点 |
|------|------|
| 运行时动态扩展 | 会产生很多小对象 |
| 职责可任意组合 | 调试时堆栈较深 |
| 比继承更灵活 | 需确保 Decorator 语义正确 |

### 何时使用
- 需要在运行时动态添加职责
- 需要撤销某些职责
- 无法使用继承扩展（类定义 final 或子类爆炸）

---

## 10. Facade — 外观模式

### 意图
为子系统中的一组接口提供一个一致的界面（高层接口）。Facade 模式定义了一个高层接口，使得子系统更容易使用。

### 动机
复杂子系统（如编译器、音视频框架、ORM）有很多类和交互。Facade 封装常用流程，让客户端不必了解内部细节。

### 结构

```
┌──────────┐      ┌─────────────┐
│  Client  │──────│   Facade    │
│          │      │+ simpleOp() │
└──────────┘      └──────┬──────┘
                         │
              ┌──────────┼──────────┐
              ↓          ↓          ↓
         ┌────────┐ ┌────────┐ ┌────────┐
         │ SubsysA│ │ SubsysB│ │ SubsysC│
         └────────┘ └────────┘ └────────┘
```

### C++ 实现要点
1. **Facade 不封装子系统全部功能**：只暴露常用操作，高级用户仍可绕过 Facade 直接访问子系统
2. **Facade 可以很小也可以很大**：可以是一个简单的函数，也可以是一个复杂的类
3. **与 Adapter 的区别**：Facade 简化接口但不改变原接口；Adapter 转换接口以兼容不同接口
4. **与 Mediator 的区别**：Facade 是对外的简化接口；Mediator 是内部对象的协调中心
5. **C++ 实现技巧**：Facade 类内部持有子系统对象的 `std::unique_ptr` 或引用

### 优缺点
| 优点 | 缺点 |
|------|------|
| 简化客户端调用 | 可能成为与所有子系统耦合的上帝类 |
| 隔离子系统变化 | 过度使用会隐藏有用功能 |
| 分层清晰 | |

### 何时使用
- 需要为复杂子系统提供简单接口
- 客户端与抽象实现类之间存在大量依赖
- 需要构建分层系统

---

## 11. Flyweight — 享元模式

### 意图
运用共享技术有效地支持大量细粒度的对象。

### 动机
游戏中可能有数千个相同外观的树木、文档中有大量相同字体的字符。如果每个对象都独立存储所有数据，内存开销巨大。Flyweight 将共享数据（intrinsic）和独有数据（extrinsic）分离。

### 结构

```
┌─────────────┐      ┌─────────────┐      ┌─────────────┐
│   Client    │──────│ FlyweightFactory│    │  Flyweight  │
│ (extrinsic) │      │ - flyweights  │      │ - intrinsic │
│             │      │ + getFlyw()   │      │ + operation()│
│             │      │               │      │   (extrinsic)│
└─────────────┘      └─────────────┘      └──────┬──────┘
                                                  │
                                           ┌──────┴──────┐
                                           │ConcreteFlyw.│
                                           │ + operation │
                                           └─────────────┘
```

### C++ 实现要点
1. **分离 intrinsic/extrinsic state**：intrinsic（共享，如字符字形、颜色）存储在 Flyweight；extrinsic（独有，如位置、坐标）由客户端传入
2. **FlyweightFactory 管理池**：`std::unordered_map<Key, std::shared_ptr<Flyweight>>`，确保同一 key 只创建一次
3. **C++23 增强**：
   - **`std::flat_map` / `std::flat_set`**：替代 `std::unordered_map`，连续内存存储，缓存友好，遍历查找更快
   - **`std::assume_aligned`**：提示编译器 Flyweight 池内存对齐，优化批量访问性能
   - **`std::expected` 查找**：`getFlyweight()` 返回 `std::expected<Flyweight, Error>`，优雅处理不存在的 key
   - **`std::println` 调试**：`std::println("Flyweight 池大小: {}", pool.size())` 类型安全输出
4. **C++20 仍可用**：`std::shared_ptr` 共享所有权；intrinsic 数据设为 `const`
5. **与 Singleton 的区别**：Flyweight 管理多个共享对象；Singleton 只有一个实例
6. **与 Object Pool 的区别**：Flyweight 强调共享状态；Object Pool 强调复用对象以减少创建开销

### 优缺点
| 优点 | 缺点 |
|------|------|
| 大幅减少内存占用 | 分离内外状态增加复杂度 |
| 运行时共享对象 | 线程安全需考虑 |
| 适合大量相似对象 | 不适用于对象差异大 |

### 何时使用
- 应用程序使用大量对象
- 对象的大部分状态可以外部化
- 用共享代替大量重复对象后，可以显著节省内存
- 对象的外在状态可以计算或存储在客户端

---

## 12. Proxy — 代理模式

### 意图
为其他对象提供一种代理以控制对这个对象的访问。

### 动机
直接访问对象可能代价高昂（大图片加载、远程服务）、不安全（需要权限控制）、或需要额外处理（缓存、日志）。Proxy 在客户端和真实对象之间插入一层。

### 结构

```
┌──────────┐      ┌──────────┐      ┌──────────┐
│  Client  │──────│  Subject │      │RealSubject│
│          │      │ + request│      │+ request │
└──────────┘      └────┬─────┘      └───────────┘
                       │                   △
                       │                   │
                  ┌────┴─────┐             │
                  │  Proxy   │─────────────┘
                  │+ request │  (持有 RealSubject)
                  │   (lazy/ │
                  │  control)│
                  └──────────┘
```

### 四种常见变体
1. **Virtual Proxy（虚拟代理）**：延迟创建开销大的对象（如图片加载器）
2. **Protection Proxy（保护代理）**：控制访问权限
3. **Remote Proxy（远程代理）**：代表远程对象（如 RPC stub）
4. **Smart Reference（智能引用）**：在访问时做额外操作（引用计数、日志）

### C++ 实现要点
1. **Proxy 与 RealSubject 实现同一接口**：客户端透明使用
2. **Virtual Proxy 的延迟加载**：`Proxy` 在第一次调用 `request()` 时才创建 `RealSubject`
3. **C++ 实现技巧**：使用 `std::unique_ptr<RealSubject>` 或 `std::optional<RealSubject>` 实现延迟构造
4. **与 Decorator 的区别**：Proxy 控制访问；Decorator 添加职责。两者结构相似但意图不同
5. **与 Adapter 的区别**：Proxy 接口相同；Adapter 接口不同

### 优缺点
| 优点 | 缺点 |
|------|------|
| 延迟初始化节省资源 | 增加一层间接 |
| 控制访问权限 | 响应可能变慢 |
| 透明代理 | 实现复杂 |

### 何时使用
- 需要延迟创建开销大的对象
- 需要控制对对象的访问权限
- 需要为对象访问添加日志、缓存等横切关注点
- 需要为远程对象提供本地代表

---

## 13. Chain of Responsibility — 职责链模式

### 意图
使多个对象都有机会处理请求，从而避免请求的发送者和接收者之间的耦合关系。将这些对象连成一条链，并沿着这条链传递请求，直到有一个对象处理它为止。

### 动机
审批系统（员工→经理→总监→CEO）中，请求的发送者不需要知道谁会处理，只需要发给链头。链可以动态重组。

### 结构

```
┌──────────┐
│  Client  │
└────┬─────┘
     │
     ↓
┌──────────┐     ┌──────────┐     ┌──────────┐
│ Handler  │────→│ Handler  │────→│ Handler  │
│ + handle│ next│ + handle│ next│ + handle│
│  (can→do)│     │  (can→do)│     │  (can→do)│
└──────────┘     └──────────┘     └──────────┘
```

### C++ 实现要点
1. **Handler 持有 next 指针**：`std::unique_ptr<Handler> next_` 或裸指针
2. **处理或转发**：`handle()` 方法判断是否能处理，不能则 `if (next_) next_->handle(request)`
3. **链的动态构建**：客户端可以任意组合处理器顺序
4. **C++23 增强**：
   - **`std::expected<T, E>` 链式错误处理**：`handle()` 返回 `std::expected<Result, Error>`，用 `and_then` 链式传递，优雅处理"无人处理"情况
   - **`std::println` 调试输出**：链式处理日志类型安全输出
   - **`std::move_only_function`**：处理函数可捕获 `unique_ptr` 资源，只移不可拷
5. **C++20 仍可用**：`std::move` 链式设置 `next_handler`；`std::function` 实现灵活处理逻辑
6. **与 Decorator 的区别**：Chain of Responsibility 处理请求并可能终止；Decorator 层层传递不终止

### 优缺点
| 优点 | 缺点 |
|------|------|
| 解耦发送者和接收者 | 请求可能无人处理 |
| 动态调整链 | 调试链式调用较麻烦 |
| 符合单一职责 | 性能可能受影响 |

### 何时使用
- 多个对象可以处理请求，处理者自动确定
- 需要在运行时指定处理者集合
- 想避免发送者与接收者硬编码

---

## 14. Command — 命令模式

### 意图
将一个请求封装为一个对象，从而使你可用不同的请求对客户进行参数化；对请求排队或记录请求日志，以及支持可撤销的操作。

### 动机
GUI 按钮的点击操作需要灵活绑定：今天绑定"打开文件"，明天绑定"打印"。Command 将操作封装为对象，支持队列、日志、撤销。

### 结构

```
┌──────────┐      ┌──────────┐      ┌──────────┐
│  Invoker │──────│ Command  │──────│ Receiver │
│+ setCmd()│      │+ execute│      │+ action()│
│+ press() │      │+ undo()  │      │          │
└──────────┘      └────┬─────┘      └──────────┘
                       │
                  ┌────┴─────────┐
                  │ConcreteCommand│
                  │+ execute()   │
                  │  (调用 Receiver)│
                  │+ undo()      │
                  └───────────────┘
```

### C++ 实现要点
1. **Command 抽象接口**：至少 `execute()` 和 `undo()`；`undo()` 需要保存执行前状态
2. **Receiver 是真正执行者**：Command 不直接干活，而是委托给 Receiver，这样 Command 只负责封装调用逻辑
3. **宏命令**：一个 `MacroCommand` 持有 `std::vector<std::unique_ptr<Command>>`，顺序执行/撤销
4. **Undo 历史栈**：Invoker 维护 `std::vector<std::unique_ptr<Command>> history`，支持多级撤销
5. **C++23 增强**：
   - **`std::move_only_function`**：绑定捕获 `unique_ptr` 的 lambda（只移不可拷），替代 `std::function` 的拷贝限制
   - **`std::expected` 错误处理**：`execute()` 返回 `std::expected<void, Error>`，撤销失败可追踪
   - **`std::println` 日志**：命令执行日志用 `std::println("[{}] 执行", cmd_name_)` 类型安全输出
6. **C++20 仍可用**：`std::function` 简化简单命令；lambda + `std::bind` 捕获 Receiver 和参数

### 优缺点
| 优点 | 缺点 |
|------|------|
| 解耦调用者与执行者 | 类数量增加 |
| 支持撤销/重做 | 命令对象可能占用大量内存 |
| 支持队列和日志 | |
| 容易组合成宏命令 | |

### 何时使用
- 需要参数化对象以执行操作
- 需要在不同时间指定、排队、执行请求
- 需要支持撤销
- 需要记录日志以便系统崩溃后恢复

---

## 15. Interpreter — 解释器模式

### 意图
给定一个语言，定义它的文法的一种表示，并定义一个解释器，这个解释器使用该表示来解释语言中的句子。

### 动机
当需要处理简单领域特定语言（DSL）如正则表达式、配置文件、简单计算表达式时，可以构建抽象语法树（AST）并递归解释。

### 结构

```
┌─────────────────┐
│AbstractExpression │
│ + interpret()   │
└───────┬─────────┘
        │
   ┌────┴────┐
   │         │
┌──┴──┐  ┌───┴───────┐
│Term.│  │NonTerm.   │
│     │  │- children │
│value│  │+ interpret│
│     │  │ (递归)     │
└─────┘  └───────────┘
```

### C++ 实现要点
1. **构建 AST**：表达式解析为树，`TerminalExpression` 是叶子节点，`NonterminalExpression` 是内部节点（运算符）
2. **递归解释**：`interpret()` 在叶子节点返回值，在内部节点递归计算子节点
3. **Context 可选**：存储全局变量、符号表等
4. **现代 C++ 中很少手写**：现代 C++ 项目通常用 ANTLR、Bison、LLVM 等工具生成解释器；本模式重在理解递归组合结构
5. **C++ 实现技巧**：用 `std::variant` 或 `std::shared_ptr` 管理 AST 节点；用访问者遍历 AST

### 优缺点
| 优点 | 缺点 |
|------|------|
| 易于扩展文法 | 复杂文法难以维护 |
| 文法实现直观 | 性能通常不如编译型 |
| 适合简单 DSL | 不适用于复杂语言 |

### 何时使用
- 语言的文法相对简单
- 效率不是关键约束
- 需要频繁解析和评估表达式

---

## 16. Iterator — 迭代器模式

### 意图
提供一种方法顺序访问一个聚合对象中各个元素，而又不需暴露该对象的内部表示。

### 动机
不同数据结构（数组、链表、树、图）的遍历方式不同。Iterator 抽象遍历接口，客户端使用统一方式遍历所有聚合。

### 结构

```
┌──────────┐      ┌──────────┐
│ Iterator │      │ Aggregate│
│+ first() │      │+ createIt│
│+ next()  │      │          │
│+ isDone()│      │          │
│+ current()│     │          │
└────┬─────┘      └────┬─────┘
     │                 │
┌────┴─────┐     ┌─────┴─────┐
│ConcreteIt│     │ConcreteAgg│
│+ next()  │     │+ createIt │
│...       │     │           │
└──────────┘     └───────────┘
```

### C++ 实现要点
1. **C++ STL 迭代器即此模式**：`std::vector::iterator`, `std::map::iterator` 都是 Iterator 模式的实现
2. **自定义容器实现**：重载 `begin()` / `end()`，返回自定义 Iterator；Iterator 重载 `operator*`, `->`, `++`, `==`, `!=`
3. **迭代器类型**：前向、双向、随机访问、输入、输出迭代器（C++ 标准定义了五种迭代器类别）
4. **C++23 增强**：
   - **`std::generator` (协程)**：C++23 协程生成器替代手写迭代器类，`co_yield` 懒加载遍历树节点，代码量锐减
   - **`std::ranges::contains` / `std::ranges::fold_left`**：遍历算法中判断包含、累加等操作更简洁
   - **`std::mdspan`**：多维数组视图，适合矩阵/网格结构的迭代器
5. **C++20 仍可用**：实现 `const_iterator` 和 `reverse_iterator` 增强可用性；使用 `std::iterator_traits` 兼容 STL 算法
6. **与 Visitor 的区别**：Iterator 遍历并访问；Visitor 对结构中的元素执行操作

### 优缺点
| 优点 | 缺点 |
|------|------|
| 统一遍历接口 | 对简单集合可能过度设计 |
| 隐藏内部结构 | |
| 支持多种遍历方式 | |

### 何时使用
- 需要访问聚合对象内容而不暴露内部结构
- 需要支持多种遍历方式（前序、后序、层次）
- 需要为不同聚合提供统一遍历接口

---

## 17. Mediator — 中介者模式

### 意图
用一个中介对象来封装一系列的对象交互。中介者使各对象不需要显式地相互引用，从而使其耦合松散，而且可以独立地改变它们之间的交互。

### 动机
聊天室中，用户 A 发送消息，不需要知道用户 B/C/D 的存在，只需要发给聊天室，由聊天室转发。避免了 N:N 的引用关系。

### 结构

```
┌──────────┐      ┌──────────┐      ┌──────────┐
│ColleagueA│──────│ Mediator │──────│ColleagueB│
│          │      │+ notify()│      │          │
└──────────┘      └────┬─────┘      └──────────┘
                       │
                  ┌────┴─────┐
                  │ConcreteM.│
                  │+ notify()│
                  │ (转发)    │
                  └──────────┘
```

### C++ 实现要点
1. **Colleague 只认识 Mediator**：不直接引用其他 Colleague，所有通信通过 `mediator_->notify(this, event)`
2. **ConcreteMediator 管理所有 Colleague**：通常持有 `std::vector<Colleague*>`，负责转发消息
3. **与 Observer 的区别**：Mediator 集中协调多对象交互；Observer 是一对多的通知机制
4. **与 Facade 的区别**：Facade 对外简化接口；Mediator 对内协调对象交互
5. **C++23 增强**：
   - **`std::move_only_function`**：Mediator 注册回调可绑定只移不可拷的 lambda，替代 `std::function`
   - **`std::expected` 转发结果**：`notify()` 返回 `std::expected<void, RoutingError>`，处理无效路由
   - **`std::println` 消息日志**：`std::println("[{}] → [{}]: {}", sender, receiver, msg)` 类型安全输出
   - **`std::flat_map`**：管理 Colleague 路由表，缓存友好
6. **C++20 仍可用**：Mediator 接口用 `notify(sender, event, data)` 参数化；用 `std::function` 注册回调

### 优缺点
| 优点 | 缺点 |
|------|------|
| 减少对象间耦合 | 中介者可能过于复杂 |
| 集中管理交互 | 中介者成为单点故障 |
| 易于修改交互逻辑 | |

### 何时使用
- 一组对象以复杂方式通信
- 对象间多对多依赖导致难以维护
- 需要封装对象间的交互行为

---

## 18. Memento — 备忘录模式

### 意图
在不破坏封装性的前提下，捕获一个对象的内部状态，并在该对象之外保存这个状态。这样以后就可将该对象恢复到原先保存的状态。

### 动机
文本编辑器的撤销功能：需要保存编辑器状态，但不应该把内部数据结构暴露给外部管理。Memento 在不破坏封装的前提下保存快照。

### 结构

```
┌──────────┐      ┌──────────┐      ┌──────────┐
│Originator│──────│ Memento  │──────│ Caretaker│
│+ save()  │      │- state   │      │- history │
│+ restore()│     │ (friend) │      │+ undo()  │
│+ setState│      │+ getState│      │          │
└──────────┘      └──────────┘      └──────────┘
```

### C++ 实现要点
1. **Memento 不暴露 Originator 细节**：Memento 的数据成员设为 `private`，只有 Originator 是其 `friend` 可以访问
2. **Caretaker 只管理 Memento，不查看内容**：Caretaker 持有 `std::vector<std::unique_ptr<Memento>>`，但不调用 Memento 的方法
3. **C++ 实现技巧**：Memento 构造函数设为 `private`，Originator 作为 `friend`；用 `std::stack` 管理撤销历史
4. **与 Command 的 undo 区别**：Command 的 undo 保存的是操作逻辑；Memento 保存的是对象状态快照
5. **深拷贝 vs 浅拷贝**：如果 Originator 包含指针，Memento 需要做深拷贝

### 优缺点
| 优点 | 缺点 |
|------|------|
| 不破坏封装 | 保存状态可能消耗大量内存 |
| 简化 Originator | 管理历史成本 |
| 支持多级撤销 | |

### 何时使用
- 需要保存对象状态以便恢复
- 不能违反封装原则获取状态
- 需要实现撤销功能

---

## 19. Observer — 观察者模式

### 意图
定义对象间的一种一对多的依赖关系，当一个对象的状态发生改变时，所有依赖于它的对象都得到通知并被自动更新。

### 动机
气象站数据变化时，多个显示面板（当前温度、统计图、警报）需要自动更新。Observer 让 Subject 不知道 Observer 的具体类型，只依赖抽象接口。

### 结构

```
┌──────────┐      ┌──────────┐
│  Subject │      │ Observer │
│+ attach()│      │+ update()│
│+ detach()│      │          │
│+ notify()│      │          │
└────┬─────┘      └────┬─────┘
     │                 │
┌────┴─────┐     ┌─────┴─────┐
│ConcreteS.│     │ConcreteObs│
│+ state   │     │+ update() │
│+ notify()│    │ (pull/push)│
└──────────┘     └───────────┘
```

### C++ 实现要点
1. **Push vs Pull 模型**：Push 模型在 `notify()` 时传递数据；Pull 模型通知 Observer 后，Observer 主动从 Subject 拉取数据
2. **避免悬空指针**：Subject 析构时通知所有 Observer 移除引用；或 Observer 在析构时自动 detach
3. **C++23 增强**：
   - **`std::move_only_function`**：Observer 回调可捕获 `unique_ptr` 资源（如只移不可拷的 UI 句柄），替代 `std::function` 的拷贝限制
   - **`std::println` 通知日志**：`std::println("[Observer] {} 收到通知", name_)` 类型安全输出
   - **`std::ranges` 遍历**：`std::ranges::for_each(observers_, ...)` 通知所有观察者
4. **C++20 仍可用**：`std::vector<std::weak_ptr<Observer>>` 解决生命周期问题；`std::list` 支持遍历中删除
5. **与 Mediator 的区别**：Observer 是一对多通知；Mediator 是多对多协调
6. **C++ 标准实现**：`std::function` + `std::vector` 是实现 Observer 的轻量方式；Boost.Signals2 提供更完善的信号槽机制

### 优缺点
| 优点 | 缺点 |
|------|------|
| 松散耦合 | 通知顺序可能隐含依赖 |
| 支持广播 | 可能意外循环触发 |
| 可动态增删观察者 | 内存泄漏风险（Observer 未 detach） |

### 何时使用
- 一个对象的状态改变需要通知其他对象，且对象数量未知
- 对象需要通知其他对象，但不知道具体是谁
- 需要抽象出依赖关系

---

## 20. State — 状态模式

### 意图
允许一个对象在其内部状态改变时改变它的行为。对象看起来似乎修改了它的类。

### 动机
自动售货机在不同状态下（无硬币、有硬币、售出、售空）对同一操作（投币、退币、转动曲柄）有不同的反应。用状态机替代大量 if-else。

### 结构

```
┌──────────┐      ┌──────────┐
│  Context │──────│  State   │
│+ request │      │+ handle()│
│- state_  │      │          │
└──────────┘      └────┬─────┘
                       │
        ┌──────────────┼──────────────┐
        │              │              │
   ┌────┴────┐    ┌────┴────┐   ┌────┴────┐
   │StateA   │    │StateB   │   │StateC   │
   │+ handle │    │+ handle │   │+ handle │
   │ (change)│    │ (change)│   │ (change)│
   └─────────┘    └─────────┘   └─────────┘
```

### C++ 实现要点
1. **Context 委托所有行为给 State**：`Context::request()` 内部调用 `state_->handle(this)`
2. **状态转换可以在 State 或 Context 中**：State 中 `handle()` 返回 `new StateX()` 更自然；Context 中集中管理更可控
3. **C++23 增强**：
   - **`std::to_underlying`**：枚举状态转底层值：`std::to_underlying(State::HasCoin)`，便于日志和调试
   - **`std::expected` 状态转换**：`handle()` 返回 `std::expected<std::unique_ptr<State>, TransitionError>`，无效转换可追踪
   - **`std::println` 状态日志**：`std::println("状态转移: {} → {}", old_state, new_state)` 类型安全输出
   - **`if constexpr` 编译期状态表**：简单状态机可用 `if constexpr` 构建编译期状态表，零开销
4. **C++20 仍可用**：`std::unique_ptr<State>` 管理状态；`context->transitionTo(std::make_unique<NewState>())`
5. **与 Strategy 的区别**：State 中状态由内部驱动，各状态互相知道，可自主转换；Strategy 由外部注入，策略互不相知
6. **状态表 vs 状态模式**：简单状态机可用二维表（状态 x 事件 → 动作/新状态）；复杂状态机用 State 模式更清晰

### 优缺点
| 优点 | 缺点 |
|------|------|
| 消除大量条件分支 | 类数量增加 |
| 状态行为集中 | 状态转换逻辑分散 |
| 易于新增状态 | 简单状态机可能过度设计 |

### 何时使用
- 对象行为取决于状态，且运行时状态改变
- 操作中有大量条件分支根据状态改变
- 状态数量多且状态转换复杂

---

## 21. Strategy — 策略模式

### 意图
定义一系列的算法，把它们一个个封装起来，并且使它们可相互替换。策略模式使得算法可独立于使用它的客户而变化。

### 动机
排序算法有多种（快排、归并、冒泡），客户端希望在运行时选择。Strategy 将算法族抽象为接口，运行时切换。

### 结构

```
┌──────────┐      ┌──────────┐
│  Context │──────│ Strategy │
│+ execute()│     │+ algorithm│
│- strategy_│    │          │
└──────────┘      └────┬─────┘
                       │
        ┌──────────────┼──────────────┐
        │              │              │
   ┌────┴────┐    ┌────┴────┐   ┌────┴────┐
   │StrategyA│    │StrategyB│   │StrategyC│
   │+ alg()  │    │+ alg()  │   │+ alg()  │
   └─────────┘    └─────────┘   └─────────┘
```

### C++ 实现要点
1. **Context 持有 Strategy 引用/指针**：构造函数注入或 setter 注入，运行时切换
2. **C++ 泛型策略**：如果策略在编译期确定，可用模板参数替代虚函数（零开销抽象）：`Sorter<QuickSort>`
3. **与 State 的区别**：Strategy 由外部注入，策略之间互不相知；State 由内部驱动，状态之间互相知道
4. **与 Template Method 的区别**：Strategy 用组合，运行时切换算法；Template Method 用继承，编译期确定算法骨架
5. **C++23 增强**：
   - **`std::move_only_function`**：策略 lambda 可捕获 `unique_ptr` 资源，只移不可拷，替代 `std::function`
   - **`std::expected` 错误处理**：策略执行返回 `std::expected<Result, StrategyError>`，调用方必须处理错误
   - **`std::ranges` 算法**：策略内部处理集合时，用 `std::ranges::sort`, `std::ranges::fold_left` 等更简洁
   - **`if constexpr`**：编译期策略选择，替代 CRTP 的部分场景
6. **C++20 仍可用**：`std::function` 作为轻量级策略；`std::unique_ptr<Strategy>` 管理所有权

### 优缺点
| 优点 | 缺点 |
|------|------|
| 算法可独立变化 | 客户端需要了解策略差异 |
| 消除条件分支 | 类数量增加 |
| 易于扩展算法 | 策略切换有开销（虚函数） |

### 何时使用
- 多个类仅在行为上不同
- 需要多种算法变体
- 算法包含客户不应该知道的数据结构
- 一个类定义了很多行为，通过多个条件语句切换

---

## 22. Template Method — 模板方法模式

### 意图
定义一个操作中的算法的骨架，而将一些步骤延迟到子类中。模板方法使得子类可以不改变一个算法的结构即可重定义该算法的某些特定步骤。

### 动机
数据挖掘流程：打开文件→解析→分析→生成报告→关闭。不同格式（CSV、JSON、XML）的解析步骤不同，但流程骨架相同。

### 结构

```
┌─────────────────┐
│  AbstractClass  │
├─────────────────┤
│+ templateMethod()│  ← 非虚，定义骨架
│  { step1();     │
│    step2();     │
│    step3(); }   │
│- step1()        │  ← 纯虚或默认实现
│- step2()        │
│- step3()        │
└───────┬─────────┘
        │
   ┌────┴────┐
   │ConcreteC.│
   │+ step1()│
   │+ step2()│
   └─────────┘
```

### C++ 实现要点
1. **好莱坞原则**："Don't call us, we'll call you." 基类定义骨架，子类填充细节
2. **钩子（Hook）**：基类提供带默认实现的虚函数，子类可以选择性重写；纯虚函数则必须重写
3. **C++23 增强**：
   - **`if constexpr` 编译期钩子**：在模板基类中，用 `if constexpr (has_feature_v<T>)` 条件编译钩子，替代部分虚函数
   - **显式对象参数** (`this T&&`)：模板方法中的步骤可用 `auto step1(this auto&& self)` 完美转发，省 4 份重载
   - **`std::println` 日志**：模板方法执行流程用 `std::println("步骤 {}: {}", i, step_name)` 类型安全输出
   - **`std::expected` 错误处理**：步骤返回 `std::expected<void, StepError>`，模板方法可统一处理失败
4. **C++20 仍可用**：模板方法设为 `public` 非虚；步骤设为 `protected virtual` 或 `private virtual`（NVI 惯用法）
5. **与 Strategy 的区别**：Template Method 用继承，编译期确定骨架；Strategy 用组合，运行时切换整个算法
6. **与 Factory Method 的关系**：Factory Method 常作为 Template Method 中的一个步骤

### 优缺点
| 优点 | 缺点 |
|------|------|
| 复用算法骨架 | 继承限制灵活性 |
| 子类只需关注差异 | 子类可能覆盖太多 |
| 控制反转 | 框架复杂 |

### 何时使用
- 一次性实现算法不变部分，子类实现可变部分
- 子类间公共行为提取到基类避免代码重复
- 需要控制子类扩展（只允许特定点扩展）

---

## 23. Visitor — 访问者模式

### 意图
表示一个作用于某对象结构中的各元素的操作。它使你可以在不改变各元素的类的前提下定义作用于这些元素的新操作。

### 动机
图形编辑器中，图形（Circle、Rectangle、Triangle）已有类层次。现在要新增"导出 SVG"、"计算面积"、"碰撞检测"等操作，但这些操作不应该污染图形类。Visitor 把操作从元素类中分离。

### 结构

```
┌──────────┐      ┌──────────┐
│  Visitor │      │  Element │
│+ visitA()│      │+ accept()│
│+ visitB()│      │          │
└────┬─────┘      └────┬─────┘
     │                 │
┌────┴─────┐      ┌────┴─────┐
│ConcreteV.│      │ConcreteE.│
│+ visitA()│      │+ accept() │
│  (操作A) │      │  v.visit(*this)│
│+ visitB()│      └──────────┘
│  (操作B) │
└──────────┘
```

### C++ 实现要点
1. **双重分发（Double Dispatch）**：`element->accept(visitor)` 调用 `visitor.visit(*element)`，运行时根据元素类型和操作类型共同决定执行哪个代码
2. **Visitor 接口为每种 Element 声明 visit 重载**：`visit(Circle&), visit(Rectangle&)` —— 这是关键，让编译器做静态分派
3. **C++23 增强**：
   - **`std::visit` + `std::variant` + `std::expected`**：C++17 `std::variant` 替代传统 Visitor，C++23 可结合 `std::expected` 处理访问错误（如访问无效节点）
   - **`std::ranges` 遍历元素**：`std::ranges::for_each(shapes_, visitor)` 批量访问元素集合
   - **`std::println` 格式化输出**：Visitor 操作日志用 `std::println("访问 {} 面积: {}", shape.name(), area)` 类型安全
   - **`if constexpr` 编译期分支**：在泛型 Visitor 中，用 `if constexpr (std::is_same_v<T, Circle>)` 替代部分运行时分发
4. **C++20 仍可用**：`accept()` 中 `visitor.visit(*this)` 利用 `this` 的静态类型调用正确的重载；元素类型很多时 `std::variant` + `std::visit` 替代
5. **与 Strategy 的区别**：Strategy 封装一个算法；Visitor 封装多个作用于不同元素的操作
6. **缺点与替代**：Visitor 增加新元素类型困难（需要修改所有 Visitor）；C++17 `std::visit` + `std::variant` 是现代替代方案

### 优缺点
| 优点 | 缺点 |
|------|------|
| 新增操作容易 | 新增元素类型困难 |
| 相关操作集中 | 破坏封装 |
| 元素类更干净 | 双重分发认知门槛高 |

### 何时使用
- 对象结构稳定，但操作经常变化
- 需要多个不相关的操作作用于同一结构
- 需要避免操作逻辑污染元素类

---

## A. 设计原则速查

| 原则 | 核心思想 | 相关模式 |
|------|---------|---------|
| **单一职责 (SRP)** | 一个类只有一个引起变化的原因 | 所有模式 |
| **开闭原则 (OCP)** | 对扩展开放，对修改封闭 | Strategy, Decorator, Template Method |
| **里氏替换 (LSP)** | 子类可以替换父类 | 所有继承-based 模式 |
| **依赖倒置 (DIP)** | 依赖抽象，不依赖具体 | Factory, Strategy, Observer |
| **接口隔离 (ISP)** | 客户端不依赖它不需要的接口 | Adapter, Facade |
| **组合复用 (CRP)** | 优先使用组合而非继承 | Strategy, Decorator, Bridge |
| **迪米特法则 (LoD)** | 最小知识原则，只与直接朋友通信 | Facade, Mediator |
| **好莱坞原则** | 别调用我们，我们会调用你 | Template Method, Observer |

---

## B. 模式对比表

| 对比 | 关键区别 |
|------|---------|
| **Strategy vs State** | Strategy 由外部注入，算法互不相知；State 由内部驱动，状态间互相知道并可转换 |
| **Decorator vs Proxy** | Decorator 添加职责（接口不变）；Proxy 控制访问（接口不变但意图不同）；两者结构相似 |
| **Decorator vs Adapter** | Decorator 保持接口并添加职责；Adapter 转换接口 |
| **Factory Method vs Abstract Factory** | Factory Method 创建单个产品；Abstract Factory 创建一族产品 |
| **Template Method vs Strategy** | Template Method 用继承，编译期确定骨架；Strategy 用组合，运行时切换算法 |
| **Facade vs Mediator** | Facade 对外简化子系统接口；Mediator 对内协调多个对象交互 |
| **Observer vs Mediator** | Observer 一对多通知；Mediator 多对多协调 |
| **Bridge vs Adapter** | Bridge 设计时分离抽象与实现；Adapter 运行时适配已有接口 |
| **Composite vs Decorator** | Composite 表示树形结构（多子）；Decorator 包装单个对象（单子） |
| **Command vs Memento** | Command 保存操作以便撤销；Memento 保存状态快照以便恢复 |
| **Flyweight vs Singleton** | Flyweight 管理多个共享对象；Singleton 只有一个实例 |
| **Flyweight vs Object Pool** | Flyweight 共享状态；Object Pool 复用对象减少创建开销 |

---

## C. C++ 实现要点

### 智能指针选择
| 场景 | 推荐 |
|------|------|
| 唯一所有权 | `std::unique_ptr<T>` |
| 共享所有权 | `std::shared_ptr<T>` |
| 弱引用（避免循环） | `std::weak_ptr<T>` |
| 观察者列表 | `std::weak_ptr<Observer>` |
| 工厂返回 | `std::unique_ptr<Product>` |

### 虚函数 vs 模板
| 场景 | 推荐 |
|------|------|
| 运行时多态 | 虚函数 + 继承 |
| 编译期多态 | 模板 + CRTP |
| 策略编译期确定 | `Context<Strategy>` 模板 |
| 策略运行期确定 | `std::unique_ptr<Strategy>` |

### 现代 C++ 替代方案
| 模式 | 现代替代 | 说明 |
|------|---------|------|
| Visitor | `std::variant` + `std::visit` | C++17 起可用，避免双重分发 |
| Strategy | `std::function` | 轻量级，无需派生类 |
| Observer | `std::function` + `std::vector` | 或 Boost.Signals2 |
| Iterator | STL 迭代器 | 直接复用 |
| Command | lambda + `std::bind` | 简单命令无需类 |
| Singleton | Meyer's Singleton | 局部 static 线程安全 |
| Prototype | `std::clone_ptr` (C++23) | 或用拷贝构造函数 |
| Builder | 显式对象参数 (C++23) | 用 `this T&&` 实现完美转发构造链 |

### C++23 亮点特性速查
| 特性 | 适用模式 | 示例 |
|------|---------|------|
| **`std::clone_ptr` / `std::cloneable`** | Prototype | 基类 `clone()` 返回 `std::clone_ptr<T>`，省手写虚 clone |
| **`std::expected<T, E>`** | Chain of Responsibility, Command | 替代异常，链式错误处理：`expected<void, Error>` |
| **`std::optional` monadic ops (`and_then`, `or_else`, `transform`)** | Builder, Facade | 链式处理可选值：`opt.and_then(...).or_else(...)` |
| **`std::print` / `std::println`** | 所有模式 | 替代 `std::cout <<`，类型安全、格式化 |
| **`std::to_underlying`** | State, Strategy | 枚举转底层值：`to_underlying(StateEnum)` |
| **`if constexpr`** | Template Method, Strategy | 编译期分支，替代 SFINAE 和 CRTP 的部分场景 |
| **显式对象参数 (`this T&&`)** | Builder, Decorator, Proxy | 完美转发成员函数，省重载 4 份 |
| **`std::mdspan`** | Composite | 多维数组视图，适合矩阵/网格树节点 |
| **`std::generator` (C++23 Coroutines)** | Iterator | 协程生成器替代手写迭代器类 |
| **`std::move_only_function`** | Strategy, Observer | 绑定 `unique_ptr` 捕获的 lambda，只移不可拷 |
| **`std::flat_map` / `std::flat_set`** | Flyweight, Prototype Registry | 用连续内存替代 `std::unordered_map`，缓存友好 |
| **`std::ranges` 新算法** | Strategy, Iterator | `std::ranges::contains`, `std::ranges::fold_left` |
| **缩略 lambda (`[_]` 捕获)** | Command, Strategy | 更简洁的 lambda 捕获语法 |
| **`std::assume_aligned`** | Flyweight, Composite | 提示编译器内存对齐，优化批量访问 |

### 常见陷阱
1. **菱形继承**：类适配器（多重继承）可能遇到问题，优先对象适配器
2. **深拷贝 vs 浅拷贝**：Prototype、Memento、Flyweight 中特别注意
3. **循环引用**：Observer 中 Subject 和 Observer 互相引用，用 `weak_ptr` 打破
4. **线程安全**：Singleton、Flyweight、Observer 在多线程中需要额外保护
5. **虚析构函数**：基类必须有虚析构函数，否则 `delete` 派生类对象通过基类指针会 UB
6. **NVI 惯用法**：Non-Virtual Interface — `public` 非虚函数调用 `private virtual` 实现，是 Template Method 在 C++ 中的最佳实践
7. **C++23 `std::print` 格式化字符串**：使用 `std::format` 风格，避免 `<<` 运算符重载污染
8. **`std::expected` 必须检查**：不要忽略 `std::expected` 的错误值，否则失去意义

---

> **如何使用本手册**：每个模式阅读顺序建议：意图 → 动机 → 结构 → 实现要点 → 查看 `/src/` 下对应目录的 `main.cpp` 模板 → 动手实现 → 对照优缺点反思。第二轮学习时重点看「模式对比表」，理解相似模式间的本质差异。
