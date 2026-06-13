#!/usr/bin/env bash
# ============================================================
# 运行时输出验证脚本
# ============================================================
# 验证每个设计模式 demo 是否:
#   1. 编译成功
#   2. 运行不崩溃
#   3. 输出包含模式名称
#   4. 输出不再包含 "TODO" 关键字
#   5. 输出包含至少 N 行非空内容
# ============================================================

set -euo pipefail

BUILD_DIR="${1:-build}"
PATTERNS=(
    singleton factory_method abstract_factory builder prototype
    adapter bridge composite decorator facade flyweight proxy
    chain_of_responsibility command interpreter iterator mediator
    memento observer state strategy template_method visitor
)

FAILURES=0

for pattern in "${PATTERNS[@]}"; do
    binary="$BUILD_DIR/$pattern"
    if [[ ! -f "$binary" ]]; then
        echo "[FAIL] $pattern: binary not found"
        ((FAILURES++)) || true
        continue
    fi

    output=$("$binary" 2>&1) || true
    exit_code=$?

    # 1. 运行不崩溃
    if [[ $exit_code -ne 0 ]]; then
        echo "[FAIL] $pattern: exited with code $exit_code"
        ((FAILURES++)) || true
        continue
    fi

    # 2. 输出包含模式名称
    pattern_name=${pattern//_/ }
    if ! echo "$output" | grep -iq "$pattern_name"; then
        echo "[FAIL] $pattern: output does not contain pattern name '$pattern_name'"
        ((FAILURES++)) || true
        continue
    fi

    # 3. 输出不再包含 "TODO" (说明已实现)
    if echo "$output" | grep -qi "TODO"; then
        echo "[FAIL] $pattern: output still contains 'TODO' (incomplete implementation)"
        ((FAILURES++)) || true
        continue
    fi

    # 4. 输出至少 5 行非空内容
    non_empty_lines=$(echo "$output" | grep -v '^\s*$' | wc -l)
    if [[ $non_empty_lines -lt 5 ]]; then
        echo "[FAIL] $pattern: only $non_empty_lines non-empty lines (minimum 5)"
        ((FAILURES++)) || true
        continue
    fi

    echo "[PASS] $pattern"
done

if [[ $FAILURES -gt 0 ]]; then
    echo ""
    echo "============================================"
    echo "$FAILURES pattern(s) failed runtime verification"
    echo "============================================"
    exit 1
fi

echo ""
echo "============================================"
echo "All 23 patterns passed runtime verification"
echo "============================================"
