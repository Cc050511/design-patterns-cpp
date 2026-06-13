#!/usr/bin/env python3
"""
Add evaluation guide to all demo files
"""

import os
import glob

# Template for the guide section
guide_template = """
// ============================================
// 评测检查清单 (Evaluation Checklist)
// ============================================
// 完成本模式后，你的实现应该展示：
//
// 结构要求 (Structure):
//   - TODO: 列出需要实现的关键类/接口
//
// 行为要求 (Behavior):
//   - TODO: 列出运行时应该展示的核心行为
//
// 输出要求 (Output):
//   - 输出应包含模式名称: "=== {Pattern} Demo ==="
//   - 输出至少 5 行非空内容
//   - 输出不应包含 "TODO"
//
// 参考实现: .reference/{pattern_file}.cpp
// 评测命令: python3 scripts/evaluate.py build src
// ============================================
"""

# Pattern-specific checklists
pattern_checklists = {
    "singleton": {
        "structure": [
            "Singleton 类 (禁止外部构造)",
            "instance() 静态方法 (返回唯一实例)",
            "禁止拷贝/移动 (= delete 或 private)"
        ],
        "behavior": [
            "多次调用 instance() 返回同一实例",
            "展示实例地址相同",
            "展示延迟初始化 (lazy init)"
        ]
    },
    "factory_method": {
        "structure": [
            "Product 抽象基类",
            "ConcreteProduct 子类",
            "Creator 抽象基类 (含虚工厂方法)",
            "ConcreteCreator 子类 (重写工厂方法)"
        ],
        "behavior": [
            "通过不同 Creator 创建不同 Product",
            "展示创建过程",
            "展示产品的使用"
        ]
    },
    "abstract_factory": {
        "structure": [
            "AbstractFactory 接口 (多个 create 方法)",
            "ConcreteFactory 实现同族产品",
            "AbstractProduct 接口",
            "ConcreteProduct 实现"
        ],
        "behavior": [
            "展示一族相关产品的创建",
            "展示不同工厂创建不同产品族",
            "展示产品配套使用"
        ]
    },
    "builder": {
        "structure": [
            "Builder 接口 (定义构建步骤)",
            "ConcreteBuilder 实现步骤",
            "Director 定义构建顺序",
            "Product 最终产品"
        ],
        "behavior": [
            "展示分步骤构建",
            "展示 Director 协调构建",
            "展示不同 Builder 得到不同产品"
        ]
    },
    "prototype": {
        "structure": [
            "Prototype 基类 (含 clone 虚方法)",
            "ConcretePrototype 实现 clone",
            "Prototype Registry (可选)"
        ],
        "behavior": [
            "展示 clone 创建新对象",
            "展示原始对象和克隆对象",
            "展示克隆是独立实例"
        ]
    },
    "adapter": {
        "structure": [
            "Target 接口 (客户期望的接口)",
            "Adaptee 类 (已有不兼容类)",
            "Adapter 类 (转换接口)"
        ],
        "behavior": [
            "展示通过 Adapter 调用 Target 接口",
            "展示内部转发到 Adaptee",
            "展示不兼容接口变得兼容"
        ]
    },
    "bridge": {
        "structure": [
            "Abstraction 抽象部分",
            "Implementor 实现部分",
            "两者通过组合关联"
        ],
        "behavior": [
            "展示抽象操作委托给实现",
            "展示实现可以独立变化",
            "展示抽象和实现的独立扩展"
        ]
    },
    "composite": {
        "structure": [
            "Component 抽象基类",
            "Leaf 叶子节点",
            "Composite 组合节点 (含子节点列表)"
        ],
        "behavior": [
            "展示树形结构",
            "展示统一处理 Leaf 和 Composite",
            "展示递归操作"
        ]
    },
    "decorator": {
        "structure": [
            "Component 抽象基类",
            "ConcreteComponent 基础对象",
            "Decorator 抽象类 (继承 Component 且持有 Component*)"
        ],
        "behavior": [
            "展示装饰器添加职责",
            "展示装饰器可嵌套",
            "展示调用被装饰对象前后增强"
        ]
    },
    "facade": {
        "structure": [
            "Facade 类 (简化接口)",
            "多个 Subsystem 复杂类",
            "Facade 委托调用 Subsystem"
        ],
        "behavior": [
            "展示 Facade 简化调用",
            "展示复杂子系统内部交互",
            "展示客户端只依赖 Facade"
        ]
    },
    "flyweight": {
        "structure": [
            "Flyweight 类 (含 intrinsic state)",
            "FlyweightFactory (管理共享对象)",
            "Client 使用 extrinsic state"
        ],
        "behavior": [
            "展示共享对象减少内存",
            "展示 intrinsic state 共享",
            "展示 extrinsic state 外部传入"
        ]
    },
    "proxy": {
        "structure": [
            "Subject 接口",
            "RealSubject 真实对象",
            "Proxy 代理类 (控制访问)"
        ],
        "behavior": [
            "展示 Proxy 控制访问",
            "展示延迟创建 RealSubject",
            "展示访问前后的额外操作"
        ]
    },
    "chain_of_responsibility": {
        "structure": [
            "Handler 抽象类 (含 next 指针)",
            "ConcreteHandler 处理者",
            "链式结构"
        ],
        "behavior": [
            "展示请求沿链传递",
            "展示某个处理者处理请求",
            "展示不同处理者处理不同请求"
        ]
    },
    "command": {
        "structure": [
            "Command 接口 (execute + undo)",
            "ConcreteCommand 绑定 Receiver",
            "Invoker 调用者",
            "Receiver 执行者"
        ],
        "behavior": [
            "展示命令封装请求",
            "展示 undo 撤销操作",
            "展示命令队列/历史"
        ]
    },
    "interpreter": {
        "structure": [
            "AbstractExpression (interpret 方法)",
            "TerminalExpression 终结符",
            "NonterminalExpression 非终结符"
        ],
        "behavior": [
            "展示语法解析",
            "展示表达式求值",
            "展示 AST 递归解释"
        ]
    },
    "iterator": {
        "structure": [
            "Iterator 接口 (next, hasNext, current)",
            "Aggregate 集合接口",
            "ConcreteIterator 实现"
        ],
        "behavior": [
            "展示顺序遍历集合",
            "展示不同遍历方式",
            "展示不暴露内部结构"
        ]
    },
    "mediator": {
        "structure": [
            "Mediator 接口 (notify 方法)",
            "ConcreteMediator 协调者",
            "Colleague 同事类"
        ],
        "behavior": [
            "展示集中协调对象交互",
            "展示对象间不直接引用",
            "展示解耦效果"
        ]
    },
    "memento": {
        "structure": [
            "Memento 备忘录 (不暴露 Originator 细节)",
            "Originator 原发器",
            "Caretaker 管理者"
        ],
        "behavior": [
            "展示保存状态",
            "展示恢复状态",
            "展示不破坏封装"
        ]
    },
    "observer": {
        "structure": [
            "Subject 接口 (attach, detach, notify)",
            "Observer 接口 (update)",
            "ConcreteSubject 和 ConcreteObserver"
        ],
        "behavior": [
            "展示一对多依赖",
            "展示状态变化自动通知",
            "展示观察者注册/注销"
        ]
    },
    "state": {
        "structure": [
            "State 接口 (handle 方法)",
            "ConcreteState 每个状态",
            "Context 上下文"
        ],
        "behavior": [
            "展示状态转换",
            "展示不同状态下的不同行为",
            "展示状态由内部驱动"
        ]
    },
    "strategy": {
        "structure": [
            "Strategy 接口 (algorithm 方法)",
            "ConcreteStrategy 不同算法",
            "Context 上下文"
        ],
        "behavior": [
            "展示运行时切换算法",
            "展示不同策略不同结果",
            "展示策略独立变化"
        ]
    },
    "template_method": {
        "structure": [
            "AbstractClass (含模板方法和钩子)",
            "ConcreteClass 重写步骤",
            "模板方法定义算法骨架"
        ],
        "behavior": [
            "展示算法骨架不变",
            "展示子类定制步骤",
            "展示好莱坞原则"
        ]
    },
    "visitor": {
        "structure": [
            "Visitor 接口 (visit 方法)",
            "Element 接口 (accept 方法)",
            "ConcreteVisitor 和 ConcreteElement"
        ],
        "behavior": [
            "展示双重分发",
            "展示对元素执行新操作",
            "展示不改变元素类"
        ]
    }
}

def generate_checklist(pattern_name):
    """生成特定模式的评测清单"""
    checklist = pattern_checklists.get(pattern_name, {
        "structure": ["TODO: 添加结构检查点"],
        "behavior": ["TODO: 添加行为检查点"]
    })
    
    lines = [
        "// ============================================",
        "// 评测检查清单 (Evaluation Checklist)",
        "// ============================================",
        "// 完成本模式后，你的实现应该展示：",
        "//",
        "// 结构要求 (必须包含以下类/接口):",
    ]
    
    for item in checklist["structure"]:
        lines.append(f"//   ✓ {item}")
    
    lines.append("//")
    lines.append("// 行为要求 (运行时输出应展示):")
    
    for item in checklist["behavior"]:
        lines.append(f"//   ✓ {item}")
    
    lines.extend([
        "//",
        "// 输出要求:",
        "//   ✓ 输出应包含模式名称: \"=== {Pattern} Demo ===\"",
        "//   ✓ 输出至少 5 行非空内容",
        "//   ✓ 输出不应包含 \"TODO\"",
        "//",
        "// 参考实现: .reference/{pattern_name}.cpp",
        "// 评测命令: python3 scripts/evaluate.py build src",
        "// ============================================",
        ""
    ])
    
    return '\n'.join(lines)

def add_guide_to_file(filepath):
    """添加评测指南到文件"""
    with open(filepath, 'r') as f:
        content = f.read()
    
    # 获取模式名
    basename = os.path.basename(os.path.dirname(filepath))
    pattern_name = basename.replace('_', ' ')
    
    # 生成检查清单
    checklist = generate_checklist(basename)
    
    # 检查是否已有检查清单
    if "评测检查清单" in content:
        print(f"Skipping {filepath} - already has checklist")
        return
    
    # 在 TODO 注释前插入检查清单
    if "// TODO: 实现你的" in content:
        content = content.replace(
            "// TODO: 实现你的",
            f"{checklist}\n// TODO: 实现你的"
        )
    
    with open(filepath, 'w') as f:
        f.write(content)
    
    print(f"Updated {filepath}")

def main():
    # 查找所有 main.cpp 文件
    pattern_dirs = [
        "src/creational/*",
        "src/structural/*",
        "src/behavioral/*"
    ]
    
    for pattern_dir in pattern_dirs:
        for main_file in glob.glob(f"{pattern_dir}/main.cpp"):
            add_guide_to_file(main_file)

if __name__ == "__main__":
    main()
