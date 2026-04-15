# Singly Linked List (C)

A simple and lightweight implementation of a singly linked list in C.

The library provides a generic list container that stores elements of arbitrary type using void*.  
It includes common list operations, searching, filtering, and sorting algorithms.

---

## Features

- Generic container (void*-based)
- Basic operations:
  - create / delete
  - append / prepend / insert
  - remove / clear
- Access:
  - front / back / at
- Algorithms:
  - find / contains
  - filter
  - concat / splice
  - sorting (including experimental bogosort 😄)
- Fully tested with GoogleTest
- Doxygen-ready documentation

---

## Requirements

### Build tools
- CMake (>= 3.10 recommended)
- C compiler (C11 or newer)
- C++ compiler with C++17 support (required for tests)

### Compilers

#### Windows
- MSVC (UCRT toolset recommended)
- Use `build.ps1`

> Git Bash on Windows does not use MSVC by default.  
> Use PowerShell for MSVC builds.

#### Linux
- GCC or Clang
- Use build.sh

---
## Build scripts

### Synopsis
Helper scripts are provided for quick project configuration, building, cleaning, and test execution.

Scripts are located in:

```text
scripts/
├── build.sh
└── build.ps1
```

Run scripts from the project root directory.

### Bash Script (Linux)

```bash
./scripts/build.sh
```

Options

| Option | Description |
|--------|-------------|
`-b`, `--build-type <type>` | Build type: Debug or Release
`-j`, `--jobs <n>` | Parallel build jobs
`-c`, `--clean` | Remove build directory before configure
`-g`, `--generator <name>` | CMake generator
`-r`, `--run` | Run test executable after successful build
`-v`, `--valgrind` | Run executable with Valgrind (Debug only)

Default Values

|Default|Value|
|--------|-------------|
Build type | Release
Generator  | MinGW Makefiles
Jobs       | 2
Build dir  | build-bash
Executable | slist_test

---