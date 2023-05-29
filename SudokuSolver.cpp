
#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <stack>

#include "SudokuSolver.h"

std::array<uint8_t, 81> SudokuSolver::solve(const std::string &filePath) {
    SudokuSolver solver{};
    solver.load_csv(filePath);
    solver.solve();
//#ifdef DEBUG
    solver.print();
//#endif
    return solver.fields;
}

void SudokuSolver::load_csv(const std::string &filepath) try {
    std::ifstream sudoku_file{filepath};
    sudoku_file.exceptions(std::ios_base::failbit | std::ios_base::badbit);
    for (auto &field: fields) {
        sudoku_file >> field;
        while (field < '0' || field > '9')
            sudoku_file >> field;
    }
} catch (const std::exception &ex) {
    throw std::runtime_error{
            "Couldn't read sudoku file '" + std::string{filepath} + "'. Error occured: " + ex.what() +
            ".\nerrno: " +
            std::to_string(errno) + "\nstrerror(errno): " + strerror(errno)};
}

void SudokuSolver::print() {
    int column_counter = 0;
    for (auto n: fields) {
        std::cout << n << " ";
        if (++column_counter == 9) {
            std::cout << "\n";
            column_counter = 0;
        }
    }
    std::cout.flush();
}

namespace {
    struct Node {
        int index;
        int value;
    };
}

void SudokuSolver::solve() {
    std::stack<Node> visited;
    bool backtracked{false};
    for (int i = 0; i < fields.size(); ++i) {

        // we take the next valid value, write it to fields and write the insertion to visited
        bool insertedAValue{false};
        int checkStart{'1'};
        if (backtracked) {
            checkStart = visited.top().value;
            visited.pop();
            backtracked = false;
        } else if (fields[i] != '0') continue;

        for (int val = checkStart; val <= '9'; ++val) {
            if (validate_insertion(i, val)) {
                fields[i] = val;
                visited.push(Node{i, val});
                insertedAValue = true;
                break;
            }
        }

        if (!insertedAValue) {
            fields[i] = '0';
            backtracked = true;
            i = visited.top().index;
            i--; //correction for for loop
        }
    }
}

bool SudokuSolver::validate_insertion(int field, int val) {
    //index of first from top element of current column
    const int current_column = field % 9;
    for (int i = current_column; i < 81; i += 9) {
        if (val == fields[i])
            return false;
    }
    //row, index of first from left element of current row
    const int current_row = field / 9 * 9;
    for (int i = current_row; i < current_row + 9; ++i) {
        if (val == fields[i])
            return false;
    }
    //upper left corner of a 3x3 box
    //corners:
    // 0  3  6
    //27 30 33
    //54 57 60
    const int box_beginning = current_row / 27 * 27 + current_column / 3 * 3;
    for (int i = box_beginning; i <= box_beginning + 18; i = i + 9) {
        for (int j = i; j <= i + 2; ++j) {
            if (val == fields[j])
                return false;
        }
    }
    return true;
}
