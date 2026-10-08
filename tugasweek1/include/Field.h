#ifndef FIELD_H
#define FIELD_H

#include "Vector2D.h"
#include <vector>
#include <string>

class Field {
public:
    static constexpr double WIDTH = 9.0;       // meter (-4.5 s/d 4.5)
    static constexpr double HEIGHT = 6.0;      // meter (-3.0 s/d 3.0)
    static constexpr double CELL_SIZE = 0.5;   // meter per petak
    static constexpr int ROWS = 12;            // 6.0 / 0.5
    static constexpr int COLS = 18;            // 9.0 / 0.5
    static constexpr double GOAL_X = 4.5;      // meter
    static constexpr double GOAL_WIDTH = 3.0;  // meter (-1.5 s/d 1.5)

private:
    char grid[ROWS][COLS];

public:
    Field();

    void clearGrid();
    void setCell(int row, int col, char symbol);
    char getCell(int row, int col) const;

    // Konversi koordinat dunia (meter) ke koordinat grid (row, col)
    static bool worldToGrid(const Vector2D& worldPos, int& row, int& col);
    // Konversi koordinat grid ke pusat koordinat dunia (meter)
    static Vector2D gridToWorld(int row, int col);

    // Cek apakah posisi berada di dalam batas lapangan
    static bool isInsideField(const Vector2D& pos);

    // Cek apakah bola masuk ke gawang lawan
    static bool isGoal(const Vector2D& pos);

    // Render grid ASCII ke konsol
    void display() const;
};

#endif // FIELD_H
