/**
 * Command — 命令模式
 * ===================
 * 意图: 将一个请求封装为一个对象，从而使你可用不同的请求对客户进行参数化；
 *       对请求排队或记录请求日志，以及支持可撤销的操作。
 *
 * 练习要点:
 *   - Command 抽象接口: execute() + undo()
 *   - ConcreteCommand 绑定一个 Receiver
 *   - Invoker (调用者) 持有 Command，调用 execute()
 *   - 支持宏命令 (多个 Command 组合)
 *   - Undo 历史栈
 *
 * C++23 可选特性:
 *   - std::move_only_function 替代 std::function 绑定只移 lambda
 *   - std::expected 错误处理 (execute() 返回 expected<void, Error>)
 *   - std::print / std::println 格式化输出命令日志
 *   - 缩略 lambda ([_] 捕获) 简化 lambda 语法
 *
 * 参考角色:
 *   Command (ICommand) ← ConcreteCommand (LightOnCommand, LightOffCommand)
 *   Receiver (Light)
 *   Invoker (RemoteControl)
 */

#include <iostream>
#include <memory>
#include <string>

// ============================================
// 评测检查清单 (Evaluation Checklist)
// ============================================
// 完成本模式后，你的实现应该展示：
//
// 结构要求 (必须包含以下类/接口):
//   ✓ Command 接口 (execute + undo)
//   ✓ ConcreteCommand 绑定 Receiver
//   ✓ Invoker 调用者
//   ✓ Receiver 执行者
//
// 行为要求 (运行时输出应展示):
//   ✓ 展示命令封装请求
//   ✓ 展示 undo 撤销操作
//   ✓ 展示命令队列/历史
//
// 输出要求:
//   ✓ 输出应包含模式名称: "=== {Pattern} Demo ==="
//   ✓ 输出至少 5 行非空内容
//   ✓ 输出不应包含 "TODO"
//
// 参考实现: .reference/{pattern_name}.cpp
// 评测命令: python3 scripts/evaluate.py build src
// ============================================

// TODO: 实现你的 Command

int main() {
    std::cout << "=== Command Demo ===\n";
    // TODO
}
