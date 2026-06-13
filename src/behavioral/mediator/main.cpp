/**
 * Mediator — 中介者模式
 * =======================
 * 意图: 用一个中介对象来封装一系列的对象交互。
 *       中介者使各对象不需要显式地相互引用，从而使其耦合松散，
 *       而且可以独立地改变它们之间的交互。
 *
 * 练习要点:
 *   - Mediator 接口定义通信协议
 *   - Colleague 持有 Mediator* 引用，通过它间接通信
 *   - ConcreteMediator 管理所有 Colleague，负责转发
 *   - Colleague 只认识 Mediator，不直接认识其他 Colleague
 *
 * C++23 可选特性:
 *   - std::move_only_function 替代 std::function 绑定只移 lambda
 *   - std::expected 转发结果 (notify() 返回 expected<void, Error>)
 *   - std::flat_map 管理 Colleague 路由表 (缓存友好)
 *   - std::print / std::println 格式化输出消息日志
 *   - std::vector<Colleague*> 管理 Colleague 列表
 *
 * 参考角色:
 *   Mediator (IChatRoom) ← ConcreteMediator (ChatRoom)
 *   Colleague (User) ← 各 User 只通过 ChatRoom 通信
 */

#include <iostream>
#include <memory>
#include <string>
#include <vector>

// TODO: 实现你的 Mediator

int main() {
    std::cout << "=== Mediator Demo ===\n";
    // TODO
}
