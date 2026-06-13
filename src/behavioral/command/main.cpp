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

// TODO: 实现你的 Command

int main() {
    std::cout << "=== Command Demo ===\n";
    // TODO
}
