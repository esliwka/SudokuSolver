#include <iostream>
#include "SudokuSolver.h"

int main(int argc, char *argv[]) {

    if (argc == 1) {
        std::cout << "Please provide a csv file with sudoku you want to be solved! (with 0 as blank spaces)"
                  << std::endl;
        return 1;
    }

    const auto sudokuPath = argv[1];
    SudokuSolver::solve(sudokuPath);
    return 0;
}
