#!/usr/bin/env bash
# ============================================================
# 静态结构验证脚本
# ============================================================
# 结合 clang-tidy 代码质量检查 + 关键词结构验证，
# 确认每个 demo 是否实现了该模式的关键角色和结构。
# ============================================================

set -euo pipefail

SRC_DIR="${1:-src}"
CLANG_TIDY="${CLANG_TIDY:-clang-tidy}"
FAILURES=0

# 定义每个模式需要验证的关键角色
# 格式: 模式名:关键类名或函数名（grep -iE 正则）
declare -A STRUCTURE_CHECKS=(
    ["singleton"]="Singleton|instance|copy|Meyer|unique"
    ["factory_method"]="factory|create|Product"
    ["abstract_factory"]="Factory|create|Abstract"
    ["builder"]="Builder|build|Director"
    ["prototype"]="clone|prototype|copy"
    ["adapter"]="Adapter|Target|Adaptee"
    ["bridge"]="Bridge|Impl|Implementor"
    ["composite"]="Composite|Leaf|Component|add|remove"
    ["decorator"]="Decorator|Component|ConcreteComponent"
    ["facade"]="Facade|Subsystem"
    ["flyweight"]="Flyweight|intrinsic|extrinsic|Factory"
    ["proxy"]="Proxy|RealSubject|Subject"
    ["chain_of_responsibility"]="Handler|next|handle"
    ["command"]="Command|execute|undo|Invoker|Receiver"
    ["interpreter"]="interpret|Expression|Terminal"
    ["iterator"]="Iterator|begin|end|next|current"
    ["mediator"]="Mediator|Colleague|notify"
    ["memento"]="Memento|Originator|Caretaker|save|restore"
    ["observer"]="Observer|Subject|attach|detach|notify|update"
    ["state"]="State|Context|handle|transition"
    ["strategy"]="Strategy|Context|algorithm|execute"
    ["template_method"]="Template|Method|step|hook|virtual"
    ["visitor"]="Visitor|accept|visit|Element"
)

echo "=== Static Structure Verification ==="
echo ""

for pattern in "${!STRUCTURE_CHECKS[@]}"; do
    regex="${STRUCTURE_CHECKS[$pattern]}"
    files=$(find "$SRC_DIR" -path "*/$pattern*/main.cpp" 2>/dev/null || true)
    if [[ -z "$files" ]]; then
        echo "[FAIL] $pattern: main.cpp not found"
        ((FAILURES++)) || true
        continue
    fi

    main_file=""
    for f in $files; do
        main_file="$f"
        break
    done

    # 1. 关键词结构检查
    found=false
    for f in $files; do
        if grep -iqE "$regex" "$f"; then
            found=true
            break
        fi
    done

    if [[ "$found" == false ]]; then
        echo "[FAIL] $pattern: missing required structure ($regex)"
        ((FAILURES++)) || true
        continue
    fi

    # 2. clang-tidy 代码质量检查
    if command -v "$CLANG_TIDY" &>/dev/null; then
        warnings=$($CLANG_TIDY --config-file=.clang-tidy "$main_file" -- -std=c++23 2>/dev/null | grep -c "warning:" || true)
        if [[ "$warnings" -gt 0 ]]; then
            echo "[WARN] $pattern: clang-tidy found $warnings warning(s)"
        fi
    fi

    echo "[PASS] $pattern: structure verified"
done

if [[ $FAILURES -gt 0 ]]; then
    echo ""
    echo "============================================"
    echo "$FAILURES pattern(s) failed structure verification"
    echo "============================================"
    exit 1
fi

echo ""
echo "============================================"
echo "All patterns passed structure verification"
echo "============================================"
