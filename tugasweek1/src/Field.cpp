#include "Field.h"
#include <iostream>

Field::Field() {
    clearGrid();
}

void Field::clearGrid() {
    for (int r = 0; r < ROWS; r++) {
        for (int c = 0; c < COLS; c++) {
            grid[r][c] = '.';
        }
    }

    // Set simbol gawang lawan '#' di kolom paling kanan untuk area y in [-1.5, 1.5]
    for (int r = 0; r < ROWS; r++) {
        Vector2D worldPos = gridToWorld(r, COLS - 1);
        if (worldPos.y >= -1.5 && worldPos.y <= 1.5) {
            grid[r][COLS - 1] = '#';
        }
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
    // x in [-4.5, 4.5] -> col in [0, 17]
    // y in [-3.0, 3.0] -> row in [0, 11] (y = 3.0 adalah top / row 0)
    col = static_cast<int>(std::floor((worldPos.x + 4.5) / CELL_SIZE));
    row = static_cast<int>(std::floor((3.0 - worldPos.y) / CELL_SIZE));

    if (col == COLS) col = COLS - 1; // clamp edge
    if (row == ROWS) row = ROWS - 1; // clamp edge

    return (row >= 0 && row < ROWS && col >= 0 && col < COLS);
}

Vector2D Field::gridToWorld(int row, int col) {
    // Pusat setiap petak (cell center)
    double x = -4.5 + (col + 0.5) * CELL_SIZE;
    double y = 3.0 - (row + 0.5) * CELL_SIZE;
    return Vector2D(x, y);
}

bool Field::isInsideField(const Vector2D& pos) {
    return (pos.x >= -4.5 && pos.x <= 4.5 && pos.y >= -3.0 && pos.y <= 3.0);
}

bool Field::isGoal(const Vector2D& pos) {
    // Gawang berada di sisi kanan x >= 4.0 m dengan lebar y [-1.5, 1.5]
    return (pos.x >= 4.0 && pos.y >= -1.5 && pos.y <= 1.5);
}

void Field::display() const {
    for (int r = 0; r < ROWS; r++) {
        for (int c = 0; c < COLS; c++) {
            std::cout << grid[r][c] << (c == COLS - 1 ? "" : " ");
        }
        std::cout << "\n";
    }
}
