cmake_minimum_required(VERSION 3.16)
project(design-patterns-cpp VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ── Tests ──────────────────────────────────────────────────────────
# Templates no longer contain main() - tests validate class implementations
option(BUILD_TESTS "Build tests (requires Catch2)" ON)
if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
