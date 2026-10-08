#ifndef CAMERA_SENSOR_HPP
#define CAMERA_SENSOR_HPP

#include "Vector2D.hpp"
#include <vector>

struct GridCoord {
    int row;
    int col;

    bool operator==(const GridCoord& o) const {
        return row == o.row && col == o.col;
    }
};

class CameraSensor {
public:
    CameraSensor();

    // Menghasilkan daftar petak segitiga vision (tinggi 1.5m / 3 petak, alas 3.5m / 7 petak)
    std::vector<GridCoord> getVisionArea(int rRow, int rCol, double orientationDeg) const;

    // Cek apakah bola terlihat di dalam segitiga vision
    bool detectBall(const std::vector<GridCoord>& visionArea, int bRow, int bCol) const;

    // Cek apakah bola berada tepat di 1 petak depan robot (syarat menendang)
    bool isBallInFront(int rRow, int rCol, double orientationDeg, int bRow, int bCol) const;
};

#endif
