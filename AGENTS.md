# AGENTS.md

## What This Is

C++23 GoF 23 design patterns learning project. 23 standalone executables, each in `src/{category}/{pattern}/main.cpp`. Users implement design pattern classes and demo code. Only singleton has a complete implementation; the other 22 are empty templates.

## Build

```bash
cmake -B build -DBUILD_TESTS=ON   # CMake 3.16+, Ninja optional
cmake --build build
./build/observer                    # run any pattern
cd build && ctest --output-on-failure
```

Requires C++23 (GCC 13+, Clang 17+). `CMAKE_CXX_STANDARD` is set to 23 in root `CMakeLists.txt`.

CI uses Ninja: `cmake -B build -G Ninja -DBUILD_TESTS=ON`. Local builds default to Make.

## Evaluation

```bash
python3 scripts/evaluate.py build src
```

5-layer scoring per pattern (0-100, pass >= 75):
- Compilation (10): binary exists in `build/`
- Structure (25): regex match in `main.cpp` (e.g. `class\s+\w*Singleton`)
- Behavior (45): runtime output contains expected keywords
- Output quality (10): min 5 lines, required keywords present, no `TODO`
- Reference (10): output similarity vs `.reference/{pattern}.cpp`

Criteria defined in `scripts/evaluation_criteria.json`. Reference comparison runs from repo root — evaluate.py uses relative paths.

## Architecture Traps

1. **No double `main()`**: `main.cpp` has `int main()`. Tests use `Catch2::Catch2WithMain`. `tests/CMakeLists.txt` compiles test files WITHOUT `main.cpp`. If you link `main.cpp` into a test binary, you get a linker error.

2. **Test binary path**: Tests reference pattern binaries as `../pattern` (relative from `build/tests/` where CTest runs). NOT `./pattern` and NOT absolute paths. If you change the build directory structure, this breaks.

3. **Template headers contain keywords**: `verify_structure.sh` grep-matches keywords like `Observer|Subject|attach` against template files. The headers (block comments) intentionally contain these keywords so empty templates pass structure checks. Don't remove them.

4. **CI has `continue-on-error` on all verification steps**: Structure, runtime, and evaluation steps don't block CI. Only "build" and "verify binaries exist" are blocking. This is intentional — empty templates can't pass behavior/output checks.

5. **Underscore→space in output**: `verify_runtime.sh` converts underscores to spaces when checking output. `chain_of_responsibility` must output "chain of responsibility" (with spaces), not "chain_of_responsibility".

6. **Catch2 via FetchContent**: First build downloads Catch2 v3.5.0 from GitHub. No offline build possible without pre-fetching.

## Directory Layout

```
src/{creational,structural,behavioral}/{pattern}/main.cpp  — user templates (23)
.reference/{pattern}.cpp                                    — complete reference impls (23)
tests/{pattern}_test.cpp                                    — per-pattern test (23)
tests/all_patterns_test.cpp                                 — meta test: all test binaries exist
scripts/evaluation_criteria.json                            — per-pattern scoring rules
scripts/evaluate.py                                         — main evaluation engine
scripts/verify_structure.sh                                 — grep-based structure check
scripts/verify_runtime.sh                                   — runtime output check
```

## CI

GitHub Actions: Arch Linux (gcc, clang) + macOS (gcc, clang). Both use `cmake -B build -G Ninja -DBUILD_TESTS=ON`.

Arch Linux container quirks: needs `pacman-key --init && pacman-key --populate` before `pacman -Sy`. Needs `git` for FetchContent (Catch2). `clang-tidy` is not a standalone package.

macOS quirks: `clang-tidy` is pre-installed (don't `brew install clang-tidy`).

## Style

- `.clang-format`: LLVM style, 4-space indent, LF line endings
- `.clang-tidy`: CamelCase classes, camelBack functions, no anonymous namespaces
- Class names: PascalCase
- File naming: `snake_case` directories, `main.cpp` per pattern

## Scripts Are One-Shot

`scripts/` contains several one-shot Python/bash scripts (`add_main.py`, `clear_templates.py`, `convert_templates.py`, etc.) used during repo setup. They modify template files in bulk. Don't re-run them without understanding current state — they overwrite `src/` files.
