#!/usr/bin/env python3
import json
from pathlib import Path

base_dir = Path("/home/yun/workspace/design-patterns-cpp")

with open(base_dir / "scripts/evaluation_criteria.json") as f:
    data = json.load(f)

patterns = [
    ("creational", "singleton"),
    ("creational", "factory_method"),
    ("creational", "abstract_factory"),
    ("creational", "builder"),
    ("creational", "prototype"),
    ("structural", "adapter"),
    ("structural", "bridge"),
    ("structural", "composite"),
    ("structural", "decorator"),
    ("structural", "facade"),
    ("structural", "flyweight"),
    ("structural", "proxy"),
    ("behavioral", "chain_of_responsibility"),
    ("behavioral", "command"),
    ("behavioral", "interpreter"),
    ("behavioral", "iterator"),
    ("behavioral", "mediator"),
    ("behavioral", "memento"),
    ("behavioral", "observer"),
    ("behavioral", "state"),
    ("behavioral", "strategy"),
    ("behavioral", "template_method"),
    ("behavioral", "visitor"),
]

for category, pattern in patterns:
    main_file = base_dir / "src" / category / pattern / "main.cpp"
    if not main_file.exists():
        continue
    
    content = main_file.read_text()
    
    criteria = data['patterns'][pattern]
    name = criteria['name']
    description = criteria['description']
    
    new_header = f"""/**
 * {name} — {description}
 *
 * 实现要求：
 * 1. 设计并实现此设计模式的完整结构
 * 2. 在 main() 中演示该模式的核心交互
 * 3. 输出需包含模式名称，展示关键行为
 *
 * 评测：python3 scripts/evaluate.py build src
 * 参考：.reference/{pattern}.cpp
 */
"""
    
    import re
    new_content = re.sub(r'/\*\*.*?\*/', new_header.strip(), content, count=1, flags=re.DOTALL)
    
    with open(main_file, 'w') as f:
        f.write(new_content)
    
    print(f"Updated header: {pattern}")

print("\nAll template headers updated!")
