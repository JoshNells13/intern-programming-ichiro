#ifndef FIELD_HPP
#define FIELD_HPP

#include "Vector2D.hpp"

class Field {
public:
    static const int ROWS = 12;
    static const int COLS = 18;
    static constexpr double CELL_SIZE = 0.5;

private:
    char grid[ROWS][COLS];

public:
    Field();

    void clearGrid();
    void setCell(int row, int col, char symbol);
    char getCell(int row, int col) const;

    static bool worldToGrid(const Vector2D& worldPos, int& row, int& col);
    static Vector2D gridToWorld(int row, int col);
    static bool isGoal(const Vector2D& pos);

    void display() const;
};

#endif
