# Singly Linked List

A generic singly linked list library written in C.

The library stores elements of arbitrary type through `void *` pointers.  
It includes common list operations, searching, filtering, and sorting algorithms.

## Contents

- [Features](#features)
- [Project Structure](#project-structure)
- [Requirements](#requirements)
- [Build Instructions](#build-instructions)
- [Manual Build](#manual-build)
- [Run Tests](#run-tests)
- [Documentation](#documentation)
- [Usage Example](#usage-example)
- [Project Goals](#project-goals)
- [License](#license)

## Features

### Core operations

- Create and delete list
- Clear all elements
- Append / prepend elements
- Insert element at position
- Remove element by value
- Remove element at index
- Remove all matching elements

### Element access

- Get element by index
- Replace element at index
- Get first / last element
- Pop first / last element
- Get list size
- Check whether list is empty

### Algorithms and utilities

- Copy list
- Concatenate lists
- Splice lists
- Search element
- Count matching elements
- Check containment
- Filter elements
- Check sorted state
- Sort list
- Bogosort (educational / experimental)


## Project Structure

```text
singly-linked-list/
├── include/        # public API
├── src/            # library implementation
├── tests/          # GoogleTest unit tests
├── scripts/        # build helper scripts
├── CMakeLists.txt
├── Doxyfile
├── README.md
└── LICENSE
```

## Requirements

### Core library

- CMake (>= 3.10 recommended)
- C compiler with C11 support

### Unit tests

- C++ compiler with C++17 support
- GoogleTest

### Optional

- Doxygen
- Valgrind (Linux)


## Build Instructions

The project includes helper scripts for quick project configuration, building, cleaning, and test execution.
Scripts are located in:
```text
scripts/
├── build.sh
└── build.ps1
```
Run scripts from the project root directory.

### Linux
```bash
bash ./scripts/build.sh
```

Linux build is located in `build-bash` directory.

#### Script options

| Option | Description |
|--------|-------------|
`-b`, `--build-type <type>` | Build type: Debug or Release (Debug is default value)
`-j`, `--jobs <n>` | Parallel build jobs (Number 2 is default value)
`-c`, `--clean` | Remove build directory before configure
`-g`, `--generator <name>` | CMake generator ("Ninja" is default value)
`-r`, `--run` | Run test executable after successful build
`-v`, `--valgrind` | Run executable with Valgrind (Debug only)
`-t`, `--tests` | Enable unit tests build

Run option is supported with `--test` included.  
Valgrind option is supported with option `--run` included.

### Windows
```PowerShell
./scripts/build.ps1
```
Windows build is located in `build` directory.

#### Script options
| Option | Description |
|--------|-------------|
`-Config <name>` | Build type: Debug or Release (Debug is default value)
`-Jobs <n>` | Parallel build jobs (2 jobs is default value)
`-Clean` | Remove build directory before configure
`-Generator <name>` | CMake generator ("MinGW Makefiles" is default)
`-Run` | Run test executable after successful build
`-BuildTests` | Enable unit tests build

Run option is supported only with option -BuildTests included.

## Manual Build
```bash
cmake -S . -B build
cmake --build build
```
### Build options

- Enable tests:
```bash
cmake -S . -B build -DBUILD_TESTS=ON
```

- Disable tests:
```bash
cmake -S . -B build -DBUILD_TESTS=OFF
```

- Debug build:
```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
```

- Release build:
```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
```

## Run Tests

```bash
ctest --test-dir build --output-on-failure
```

Or run executable directly:
- Windows
```PowerShell
./build/slist_test.exe
```
- Linux
```bash
./build-bash/slist_test
```

## Documentation

Generate documentation with Doxygen:
```bash
doxygen Doxyfile
```

Location of generated HTML output:
```
docs/html/index.html
```

## Usage Example

```c
#include <stdio.h>
#include "single_list.h"

int main(void)
{
    slist_t *list = slist_create(sizeof(int));

    int a = 10;
    int b = 20;

    slist_append(list, &a);
    slist_append(list, &b);

    int *value = (int *)slist_at(list, 1);

    if (value)
        printf("%d\n", *value);

    slist_delete(&list);
    return 0;
}
```

## Project Goals

- Practice low-level API design in C
- Improve testing workflow with GoogleTest
- Build reusable generic data structures
- Maintain clean project architecture and documentation

## License

This project is licensed under the MIT License.
