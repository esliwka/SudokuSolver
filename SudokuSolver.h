
#ifndef SUDOKU_SOLVER_SUDOKUSOLVER_H
#define SUDOKU_SOLVER_SUDOKUSOLVER_H


#include <cstdint>
#include <array>
#include <string>


/// 9x9 SudokuSolver solver
class SudokuSolver {
public:
    /**
     * @param filePath Path to the csv file containing the sudoku array, where 0 means no value
     * @return Array representing the solved sudoku
     */
    static std::array<uint8_t, 81> solve(const std::string &filePath);

private:
    SudokuSolver() = default;

    void load_csv(const std::string &filepath);

    void print();

    void solve();

    bool validate_insertion(int field, int val);

    std::array<uint8_t, 81> fields;
};


#endif //SUDOKU_SOLVER_SUDOKUSOLVER_H
