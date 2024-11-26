# Archive Language

## Getting Started

### Prerequisites

Before you begin, ensure you have the following tools installed on your system:

- **[`CMake`](https://cmake.org/)**
- **[`Make`](https://www.gnu.org/software/make/)**
- `C++ 20 Compiler` (recommended:
                        **[`MSVC`](https://visualstudio.microsoft.com/downloads/)**,
                        **[`Clang`](https://releases.llvm.org/download.html)**,
                        or **[`GCC`](https://gcc.gnu.org/))**

### Building

Once you've got your build environment configured, use following steps to
compile the program:

1. Clone repo:

    ```bash
    git clone https://github.com/michael-re/archive.git
    ```

2. Navigate to project directory:

    ```bash
    cd archive/
    ```

3. Build using the provided **[`makefile`](makefile)**:

    ```bash
    # Debug build
    make debug

    # Release build
    make release

    # Clean up compiled binaries and build artifacts
    make clean
    ```
