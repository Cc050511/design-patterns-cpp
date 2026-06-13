cmake_minimum_required(VERSION 3.16)

# ── Catch2 测试子项目 ─────────────────────────────────────

Include(FetchContent)
FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG        v3.5.0
)
FetchContent_MakeAvailable(Catch2)

list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
include(Catch)

# ── 测试库: 提取 src 下的实现为可测试目标 ─────────────────
# 注意：每个 demo 的 main.cpp 是独立可执行文件，不适合直接链接。
# 测试策略：将每个模式的核心实现编译为 object library，
# 同时供 main.cpp 和 test.cpp 使用。

# 创建辅助函数：为每个模式目录添加测试
function(add_pattern_test PATTERN_NAME SRC_DIR)
    set(MAIN_CPP "${SRC_DIR}/main.cpp")
    set(TEST_CPP "${CMAKE_CURRENT_SOURCE_DIR}/${PATTERN_NAME}_test.cpp")

    if(NOT EXISTS ${MAIN_CPP})
        message(WARNING "main.cpp not found for ${PATTERN_NAME}, skipping test")
        return()
    endif()

    # 若测试文件存在，则编译
    if(EXISTS ${TEST_CPP})
        add_executable(${PATTERN_NAME}_test
            ${TEST_CPP}
            ${MAIN_CPP}
        )
        target_compile_features(${PATTERN_NAME}_test PRIVATE cxx_std_23)
        target_link_libraries(${PATTERN_NAME}_test PRIVATE Catch2::Catch2WithMain)
        target_include_directories(${PATTERN_NAME}_test PRIVATE ${CMAKE_SOURCE_DIR})
        catch_discover_tests(${PATTERN_NAME}_test)
    else()
        message(STATUS "No test file for ${PATTERN_NAME}, skipping")
    endif()
endfunction()

# ── 创建型模式 ──────────────────────────────────────────
add_pattern_test(singleton        ${CMAKE_SOURCE_DIR}/src/creational/singleton)
add_pattern_test(factory_method   ${CMAKE_SOURCE_DIR}/src/creational/factory_method)
add_pattern_test(abstract_factory ${CMAKE_SOURCE_DIR}/src/creational/abstract_factory)
add_pattern_test(builder          ${CMAKE_SOURCE_DIR}/src/creational/builder)
add_pattern_test(prototype        ${CMAKE_SOURCE_DIR}/src/creational/prototype)

# ── 结构型模式 ──────────────────────────────────────────
add_pattern_test(adapter     ${CMAKE_SOURCE_DIR}/src/structural/adapter)
add_pattern_test(bridge      ${CMAKE_SOURCE_DIR}/src/structural/bridge)
add_pattern_test(composite   ${CMAKE_SOURCE_DIR}/src/structural/composite)
add_pattern_test(decorator   ${CMAKE_SOURCE_DIR}/src/structural/decorator)
add_pattern_test(facade      ${CMAKE_SOURCE_DIR}/src/structural/facade)
add_pattern_test(flyweight   ${CMAKE_SOURCE_DIR}/src/structural/flyweight)
add_pattern_test(proxy       ${CMAKE_SOURCE_DIR}/src/structural/proxy)

# ── 行为型模式 ──────────────────────────────────────────
add_pattern_test(chain_of_responsibility ${CMAKE_SOURCE_DIR}/src/behavioral/chain_of_responsibility)
add_pattern_test(command     ${CMAKE_SOURCE_DIR}/src/behavioral/command)
add_pattern_test(interpreter ${CMAKE_SOURCE_DIR}/src/behavioral/interpreter)
add_pattern_test(iterator    ${CMAKE_SOURCE_DIR}/src/behavioral/iterator)
add_pattern_test(mediator    ${CMAKE_SOURCE_DIR}/src/behavioral/mediator)
add_pattern_test(memento     ${CMAKE_SOURCE_DIR}/src/behavioral/memento)
add_pattern_test(observer    ${CMAKE_SOURCE_DIR}/src/behavioral/observer)
add_pattern_test(state       ${CMAKE_SOURCE_DIR}/src/behavioral/state)
add_pattern_test(strategy    ${CMAKE_SOURCE_DIR}/src/behavioral/strategy)
add_pattern_test(template_method ${CMAKE_SOURCE_DIR}/src/behavioral/template_method)
add_pattern_test(visitor     ${CMAKE_SOURCE_DIR}/src/behavioral/visitor)

# ── 统一测试入口 ──────────────────────────────────────────
add_executable(all_patterns_test all_patterns_test.cpp)
target_compile_features(all_patterns_test PRIVATE cxx_std_23)
target_link_libraries(all_patterns_test PRIVATE Catch2::Catch2WithMain)
target_compile_definitions(all_patterns_test PRIVATE BINARY_DIR="${CMAKE_BINARY_DIR}")
catch_discover_tests(all_patterns_test)
