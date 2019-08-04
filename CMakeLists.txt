cmake_minimum_required(VERSION 3.14)
project(sudoku_solver VERSION 0.1
        DESCRIPTION "sudoku detection and solver"
        LANGUAGES CXX)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

set(CMAKE_CXX_STANDARD 17)

add_executable(sudoku_solver
        src/sudoku_solver.cpp
        src/sudoku_detection.cpp
        src/sudoku.h src/sudoku.cpp)

target_link_libraries(sudoku_solver
        CONAN_PKG::opencv
        CONAN_PKG::fmt)