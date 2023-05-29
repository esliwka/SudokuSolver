cmake_minimum_required(VERSION 3.23)
project(sudoku_solver)

set(CMAKE_CXX_STANDARD 23)

add_executable(sudoku_solver main.cpp SudokuSolver.cpp SudokuSolver.h)
