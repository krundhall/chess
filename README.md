# chess

A SFML-based chess game project for coursework.

## How to build

Prerequisites

Required on all platforms:

- A C++20 compatible compiler (GCC, Clang, or MSVC)
- CMake version 3.20 or later
- SFML version 2.5 or later (tested with 2.5.1)

## Windows

# Requirements

- Windows 10 or newer
- Visual Studio 2019 or later (with the “Desktop development with C++” workload installed)
- CMake available in PATH
- SFML installed (via vcpkg or official SFML binaries)

# Build steps

Clone the repository
```
git clone https://github.com/krundhall/chess.git
```

Enter the project root
```
cd chess
```

Configure the project with CMake
```
cmake -S . -B build
```

Build the project
```
cmake --build build
```

Run the executable
The executable will be located in the build directory, typically under
build\Debug\chess.exe
(or Release, depending on configuration)

Make sure the required SFML DLL files are available at runtime (either in PATH or next to the executable).

## Linux (Debian / Ubuntu)

# Requirements

- A C++20 compatible compiler
- CMake version 3.20 or later
- SFML development libraries

On Debian-based systems, SFML can be installed via the package manager.

# Build steps

Install dependencies
```
sudo apt install build-essential cmake libsfml-dev
```

Clone the repository
```
git clone https://github.com/krundhall/chess.git
```

Enter the project root
```
cd chess
```

Configure the project with CMake
```
cmake -S . -B build
```

Build the project
```
cmake --build build
```

Run the executable
```
./build/chess
```

## Notes

This project uses an out-of-source build (the build directory can be safely deleted at any time).
If SFML is not found, CMake will fail during configuration.
The project has been tested and developed primarily on Linux (through WSL 2.0).
