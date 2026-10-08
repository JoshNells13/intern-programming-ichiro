#include "CameraSensor.hpp"
#include <cmath>
#include <set>

CameraSensor::CameraSensor() {}

std::vector<GridCoord>
CameraSensor::getVisionArea(int rRow, int rCol, double orientationDeg) const {
  std::vector<GridCoord> visionCells;
  double rad = orientationDeg * PI / 180.0;

  // Vektor arah maju dan tegak lurus pada grid
  double fCol = std::cos(rad);
  double fRow = -std::sin(rad);

  double pCol = -fRow;
  double pRow = fCol;

  std::set<std::pair<int, int>> uniqueCells;

  for (int d = 1; d <= 3; d++) {
    for (int w = -d; w <= d; w++) {
      int cellRow = static_cast<int>(std::round(rRow + d * fRow + w * pRow));
      int cellCol = static_cast<int>(std::round(rCol + d * fCol + w * pCol));

      if (cellRow >= 0 && cellRow < 12 && cellCol >= 0 && cellCol < 18) {
        if (uniqueCells.insert({cellRow, cellCol}).second) {
          visionCells.push_back({cellRow, cellCol});
        }
      }
    }
  }

  return visionCells;
}

bool CameraSensor::detectBall(const std::vector<GridCoord> &visionArea,
                              int bRow, int bCol) const {
  for (const auto &cell : visionArea) {
    if (cell.row == bRow && cell.col == bCol) {
      return true;
    }
  }
  return false;
}

bool CameraSensor::isBallInFront(int rRow, int rCol, double orientationDeg,
                                 int bRow, int bCol) const {
  double rad = orientationDeg * PI / 180.0;
  int frontCol = static_cast<int>(std::round(rCol + std::cos(rad)));
  int frontRow = static_cast<int>(std::round(rRow - std::sin(rad)));

  return (frontRow == bRow && frontCol == bCol);
}
