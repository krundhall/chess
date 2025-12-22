cmake_minimum_required(VERSION 3.20)

project(Chess LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(chess)

target_sources(chess PRIVATE
    src/main.cpp
    src/Board.cpp
    src/pieces/Piece.cpp
    src/Renderer.cpp
    src/InputHandler.cpp
    src/Game.cpp
    src/pieces/Pawn.cpp
    src/pieces/Piece.cpp
)

target_include_directories(chess PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

target_link_libraries(chess PRIVATE
    sfml-graphics
    sfml-window
    sfml-system
)
