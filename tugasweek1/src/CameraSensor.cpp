#include "CameraSensor.hpp"
#include "Field.hpp"
#include <cmath>
#include <set>

CameraSensor::CameraSensor() {}

std::vector<GridCoord> CameraSensor::getVisionArea(int rRow, int rCol, double orientationDeg) const {
    std::vector<GridCoord> visionCells;
    std::set<std::pair<int, int>> uniqueCells;

    double normAngle = orientationDeg;
    while (normAngle < 0.0) normAngle += 360.0;
    while (normAngle >= 360.0) normAngle -= 360.0;

    int dirIndex = static_cast<int>(std::round(normAngle / 45.0)) % 8;

    auto addCell = [&](int r, int c) {
        if (r >= 0 && r < Field::ROWS && c >= 0 && c < Field::COLS) {
            if (r != rRow || c != rCol) {
                if (uniqueCells.insert({r, c}).second) {
                    visionCells.push_back({r, c});
                }
            }
        }
    };

    switch (dirIndex) {
        case 0: // Kanan (0 deg) - Sesuai gambar contoh
            for (int d = 1; d <= 3; d++) {
                for (int w = -d; w <= d; w++) {
                    addCell(rRow + w, rCol + d);
                }
            }
            break;

        case 2: // Atas (90 deg)
            for (int d = 1; d <= 3; d++) {
                for (int w = -d; w <= d; w++) {
                    addCell(rRow - d, rCol + w);
                }
            }
            break;

        case 4: // Kiri (180 deg)
            for (int d = 1; d <= 3; d++) {
                for (int w = -d; w <= d; w++) {
                    addCell(rRow + w, rCol - d);
                }
            }
            break;

        case 6: // Bawah (270 deg)
            for (int d = 1; d <= 3; d++) {
                for (int w = -d; w <= d; w++) {
                    addCell(rRow + d, rCol + w);
                }
            }
            break;

        case 1: // Kanan-Atas (45 deg)
            for (int d = 1; d <= 3; d++) {
                for (int k = 0; k <= d; k++) {
                    addCell(rRow - d, rCol + k);
                    addCell(rRow - k, rCol + d);
                }
            }
            break;

        case 3: // Kiri-Atas (135 deg)
            for (int d = 1; d <= 3; d++) {
                for (int k = 0; k <= d; k++) {
                    addCell(rRow - d, rCol - k);
                    addCell(rRow - k, rCol - d);
                }
            }
            break;

        case 5: // Kiri-Bawah (225 deg)
            for (int d = 1; d <= 3; d++) {
                for (int k = 0; k <= d; k++) {
                    addCell(rRow + d, rCol - k);
                    addCell(rRow + k, rCol - d);
                }
            }
            break;

        case 7: // Kanan-Bawah (315 deg)
            for (int d = 1; d <= 3; d++) {
                for (int k = 0; k <= d; k++) {
                    addCell(rRow + d, rCol + k);
                    addCell(rRow + k, rCol + d);
                }
            }
            break;
    }

    return visionCells;
}

bool CameraSensor::detectBall(const std::vector<GridCoord>& visionArea, int bRow, int bCol) const {
    for (const auto& cell : visionArea) {
        if (cell.row == bRow && cell.col == bCol) {
            return true;
        }
    }
    return false;
}

bool CameraSensor::isBallInFront(int rRow, int rCol, double orientationDeg, int bRow, int bCol) const {
    double normAngle = orientationDeg;
    while (normAngle < 0.0) normAngle += 360.0;
    while (normAngle >= 360.0) normAngle -= 360.0;

    int dirIndex = static_cast<int>(std::round(normAngle / 45.0)) % 8;

    int fRow = 0, fCol = 0;
    switch (dirIndex) {
        case 0: fRow = 0;  fCol = 1;  break;
        case 1: fRow = -1; fCol = 1;  break;
        case 2: fRow = -1; fCol = 0;  break;
        case 3: fRow = -1; fCol = -1; break;
        case 4: fRow = 0;  fCol = -1; break;
        case 5: fRow = 1;  fCol = -1; break;
        case 6: fRow = 1;  fCol = 0;  break;
        case 7: fRow = 1;  fCol = 1;  break;
    }

    return (rRow + fRow == bRow && rCol + fCol == bCol);
}
