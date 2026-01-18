# chess

A SFML-based chess game project for coursework.

## How to build

Prerequisites

Required on all platforms:

- A C++20 compatible compiler (GCC, Clang, or MSVC)
- CMake version 3.20 or later
- SFML version 2.5 or later (tested with 2.5.1)

# Windows

## Requirements

- Windows 10 or newer
- A C++ compiler (clang, gnu, mcsv)
- CMake available in PATH
- SFML installed (via vcpkg or official SFML binaries)

## Build steps

Clone the repository
```
git clone https://github.com/krundhall/chess
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

The executable will be located in the build directory, typically under
build\Debug\chess.exe
(or Release, depending on configuration)

# Linux (Debian / Ubuntu)

## Requirements

- A C++20 compatible compiler
- CMake version 3.20 or later
- SFML development libraries

On Debian-based systems, SFML can be installed via the package manager.

## Build steps

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

This project is ran from the build folder.

If SFML is not found, CMake will fail during configuration.
The project has been tested and developed primarily on Linux (through WSL 2.0).
