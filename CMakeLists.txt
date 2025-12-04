cmake_minimum_required(VERSION 3.16)
project(Chess)

set(CMAKE_CXX_STANDARD 17)

# Include header directory
include_directories(include)

# Find SFML
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# Source files
file(GLOB SOURCES
    src/*.cpp
    src/pieces/*.cpp
)

add_executable(Chess ${SOURCES})

target_link_libraries(Chess sfml-graphics sfml-window sfml-system)
