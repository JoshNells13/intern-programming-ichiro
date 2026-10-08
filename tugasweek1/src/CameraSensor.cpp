#include "CameraSensor.hpp"
#include "Field.hpp"
#include <cmath>
#include <set>

CameraSensor::CameraSensor() {}

std::vector<GridCoord> CameraSensor::getVisionArea(int rRow, int rCol, double orientationDeg) const {
    std::vector<GridCoord> vision;
    std::set<std::pair<int, int>> visited;

    double normAngle = orientationDeg;
    while (normAngle < 0.0) normAngle += 360.0;
    while (normAngle >= 360.0) normAngle -= 360.0;

    int dir = static_cast<int>(std::round(normAngle / 90.0)) % 4;
    // 0: Kanan (0 deg), 1: Atas (90 deg), 2: Kiri (180 deg), 3: Bawah (270 deg)

    auto add = [&](int r, int c) {
        if (r >= 0 && r < Field::ROWS && c >= 0 && c < Field::COLS) {
            if (r != rRow || c != rCol) {
                if (visited.insert({r, c}).second) {
                    vision.push_back({r, c});
                }
            }
        }
    };

    if (dir == 0) { // Kanan (0 deg) - Persis sesuai contoh
        for (int d = 1; d <= 3; d++) {
            for (int w = -d; w <= d; w++) {
                add(rRow + w, rCol + d);
            }
        }
    } else if (dir == 1) { // Atas (90 deg)
        for (int d = 1; d <= 3; d++) {
            for (int w = -d; w <= d; w++) {
                add(rRow - d, rCol + w);
            }
        }
    } else if (dir == 2) { // Kiri (180 deg)
        for (int d = 1; d <= 3; d++) {
            for (int w = -d; w <= d; w++) {
                add(rRow + w, rCol - d);
            }
        }
    } else if (dir == 3) { // Bawah (270 deg)
        for (int d = 1; d <= 3; d++) {
            for (int w = -d; w <= d; w++) {
                add(rRow + d, rCol + w);
            }
        }
    }

    return vision;
}

bool CameraSensor::detectBall(const std::vector<GridCoord>& visionArea, int bRow, int bCol) const {
    for (const auto& c : visionArea) {
        if (c.row == bRow && c.col == bCol) return true;
    }
    return false;
}

bool CameraSensor::isBallInFront(int rRow, int rCol, double orientationDeg, int bRow, int bCol) const {
    double normAngle = orientationDeg;
    while (normAngle < 0.0) normAngle += 360.0;
    while (normAngle >= 360.0) normAngle -= 360.0;

    int dir = static_cast<int>(std::round(normAngle / 90.0)) % 4;
    int fR = 0, fC = 0;
    switch (dir) {
        case 0: fR = 0;  fC = 1;  break; // Kanan
        case 1: fR = -1; fC = 0;  break; // Atas
        case 2: fR = 0;  fC = -1; break; // Kiri
        case 3: fR = 1;  fC = 0;  break; // Bawah
    }
    return (rRow + fR == bRow && rCol + fC == bCol);
}
