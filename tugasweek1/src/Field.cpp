#include "Field.hpp"
#include <iostream>
#include <cmath>

Field::Field() {
    clearGrid();
}

void Field::clearGrid() {
    for (int r = 0; r < ROWS; r++) {
        for (int c = 0; c < COLS; c++) {
            grid[r][c] = '.';
        }
    }
    for (int r = 3; r <= 8; r++) {
        grid[r][COLS - 1] = '#';
    }
}

void Field::setCell(int row, int col, char symbol) {
    if (row >= 0 && row < ROWS && col >= 0 && col < COLS) {
        grid[row][col] = symbol;
    }
}

char Field::getCell(int row, int col) const {
    if (row >= 0 && row < ROWS && col >= 0 && col < COLS) {
        return grid[row][col];
    }
    return ' ';
}

bool Field::worldToGrid(const Vector2D& worldPos, int& row, int& col) {
    col = static_cast<int>(std::floor((worldPos.x + 4.5) / CELL_SIZE));
    row = static_cast<int>(std::floor((3.0 - worldPos.y) / CELL_SIZE));
    if (col >= COLS) col = COLS - 1;
    if (row >= ROWS) row = ROWS - 1;
    return (row >= 0 && row < ROWS && col >= 0 && col < COLS);
}

Vector2D Field::gridToWorld(int row, int col) {
    double x = -4.5 + (col + 0.5) * CELL_SIZE;
    double y = 3.0 - (row + 0.5) * CELL_SIZE;
    return Vector2D(x, y);
}

bool Field::isGoal(const Vector2D& pos) {
    return (pos.x >= 4.0 && pos.y >= -1.5 && pos.y <= 1.5);
}

void Field::display() const {
    std::cout << "\033[H";  
    for (int r = 0; r < ROWS; r++) {
        for (int c = 0; c < COLS; c++) {
            out += grid[r][c];
            std::cout << grid[r][c] << (c == COLS - 1 ? "" : " ");
        }
            out += "\033[K\n";
    }
        out += "\033[J";
        std::cout << "\033[J" << std::flush;
}
