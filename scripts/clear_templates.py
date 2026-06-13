#!/usr/bin/env python3
import os
from pathlib import Path

base_dir = Path("/home/yun/workspace/design-patterns-cpp")

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

# Keep singleton as complete example, clear others
for i, (category, pattern) in enumerate(patterns):
    main_file = base_dir / "src" / category / pattern / "main.cpp"
    if not main_file.exists():
        continue
    
    # Singleton is kept as complete example (index 0)
    if i == 0:
        print(f"Keeping singleton as complete example")
        continue
    
    # Clear template - remove all class definitions
    content = main_file.read_text()
    
    # Extract includes and main()
    lines = content.split('\n')
    includes = []
    in_main = False
    main_lines = []
    
    for line in lines:
        if line.startswith('#include'):
            includes.append(line)
        elif 'int main()' in line:
            in_main = True
            main_lines.append(line)
        elif in_main:
            main_lines.append(line)
    
    # Rewrite with just includes and main
    pattern_name = pattern.replace('_', ' ').title()
    new_content = f"""/**
 * {pattern_name} — 模式意图
 * 意图: 请实现此设计模式
 * 评测: python3 scripts/evaluate.py build src
 * 参考: .reference/{pattern}.cpp
 */

{chr(10).join(includes) if includes else '#include <iostream>'}

// TODO: 实现此设计模式的所有类

int main() {{
    std::cout << "=== {pattern_name} Demo ===\\n";
    // TODO: 创建对象并演示设计模式
    std::cout << "{pattern_name} verified successfully.\\n";
    return 0;
}}
"""
    
    with open(main_file, 'w') as f:
        f.write(new_content)
    
    print(f"Cleared template: {pattern}")

print("\nAll templates cleared (except singleton)!")
