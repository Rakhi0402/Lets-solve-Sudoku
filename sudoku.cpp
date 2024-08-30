#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <algorithm>

#define N 9

// Function to print the Sudoku board with separators
void printBoard(const std::vector<std::vector<int>>& board) {
    for (int i = 0; i < N; i++) {
        if (i % 3 == 0 && i != 0) {
            std::cout << "=======+========+========\n";
        }
        for (int j = 0; j < N; j++) {
            if (j % 3 == 0 && j != 0) {
                std::cout << " | ";
            }
            std::cout << (board[i][j] == 0 ? " " : std::to_string(board[i][j])) << " ";
        }
        std::cout << std::endl;
    }
}

// Check if placing num at board[row][col] is valid
bool isValid(const std::vector<std::vector<int>>& board, int row, int col, int num) {
    // Check if num is not in the current row
    for (int x = 0; x < N; x++) {
        if (board[row][x] == num) {
            return false;
        }
    }
    
    // Check if num is not in the current column
    for (int x = 0; x < N; x++) {
        if (board[x][col] == num) {
            return false;
        }
    }
    
    // Check if num is not in the 3x3 sub-grid
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i + startRow][j + startCol] == num) {
                return false;
            }
        }
    }
    
    return true;
}

// Function to solve the Sudoku puzzle using backtracking
bool solveSudoku(std::vector<std::vector<int>>& board) {
    int row, col;
    bool empty = false;
    
    // Find an empty cell in the Sudoku board
    for (row = 0; row < N; row++) {
        for (col = 0; col < N; col++) {
            if (board[row][col] == 0) {
                empty = true;
                break;
            }
        }
        if (empty) {
            break;
        }
    }
    
    // No empty cell found, Sudoku is solved
    if (!empty) {
        return true;
    }
    
    // Try numbers from 1 to 9
    for (int num = 1; num <= 9; num++) {
        if (isValid(board, row, col, num)) {
            board[row][col] = num;
            // Recursively attempt to solve with the current number
            if (solveSudoku(board)) {
                return true;
            }
            // If placing num doesn't lead to a solution, reset and try next number
            board[row][col] = 0;
        }
    }
    
    // Trigger backtracking
    return false;
}

// Function to fill a Sudoku board with a valid solution
void fillBoard(std::vector<std::vector<int>>& board) {
    // Fill the diagonal 3x3 sub-grids with numbers
    for (int i = 0; i < N; i += 3) {
        for (int row = i; row < i + 3; row++) {
            for (int col = i; col < i + 3; col++) {
                std::vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9};
                std::random_shuffle(numbers.begin(), numbers.end());
                for (int num : numbers) {
                    if (isValid(board, row, col, num)) {
                        board[row][col] = num;
                        break;
                    }
                }
            }
        }
    }
    
    // Solve the filled board to ensure it's a valid solution
    solveSudoku(board);
}

// Function to remove some cells from the board to create a puzzle
void removeCells(std::vector<std::vector<int>>& board, int cellsToRemove) {
    int count = cellsToRemove;
    while (count > 0) {
        int i = std::rand() % N;
        int j = std::rand() % N;
        if (board[i][j] != 0) {
            board[i][j] = 0;
            count--;
        }
    }
}

int main() {
    std::vector<std::vector<int>> board(N, std::vector<int>(N, 0));
    int choice;
    std::cout<< "Hello Dost! How are you! Lets play with some sudoku puzzles.\n I am sure you'll enjoy.\n";
    std::cout << "Choose an option:\n";
    std::cout << "1. Generate a random solvable Sudoku puzzle\n";
    std::cout << "2. Solve an existing Sudoku puzzle\n";
    std::cout << "Enter your choice (1 or 2): ";
    std::cin >> choice;

    // Check for invalid input
    if (std::cin.fail() || (choice != 1 && choice != 2)) {
        std::cout << "Invalid choice. Please enter 1 or 2.\n";
        return 1;
    }

    switch (choice) {
        case 1: {
            // Generate a random Sudoku puzzle
            fillBoard(board);
            removeCells(board, 40); // Remove 40 cells to create the puzzle
            std::cout << "Generated Sudoku Puzzle:\n";
            printBoard(board);
            break;
        }
        case 2: {
            std::cout << "Enter your Sudoku puzzle (9x9 grid, use 0 for empty cells):\n";
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < N; j++) {
                    std::cin >> board[i][j];
                }
            }
            std::cout << "\nSolving the provided Sudoku puzzle...\n";
            if (solveSudoku(board)) {
                std::cout << "Sudoku solved successfully!\n";
                printBoard(board);
            } else {
                std::cout << "No solution exists for the provided Sudoku.\n";
            }
            break;
        }
    }

    return 0;
}

