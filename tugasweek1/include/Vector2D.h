#ifndef VECTOR2D_H
#define VECTOR2D_H

#include <cmath>
#include <iostream>

struct Vector2D {
  double x;
  double y;

  Vector2D() : x(0.0), y(0.0) {}
  Vector2D(double x, double y) : x(x), y(y) {}

  Vector2D operator+(const Vector2D &other) const {
    return Vector2D(x + other.x, y + other.y);
  }

  Vector2D operator-(const Vector2D &other) const {
    return Vector2D(x - other.x, y - other.y);
  }

  Vector2D operator*(double scalar) const {
    return Vector2D(x * scalar, y * scalar);
  }

  bool operator==(const Vector2D &other) const {
    return std::abs(x - other.x) < 1e-5 && std::abs(y - other.y) < 1e-5;
  }

  double length() const { return std::sqrt(x * x + y * y); }

  double distanceTo(const Vector2D &other) const {
    return (*this - other).length();
  }

  Vector2D normalized() const {
    double len = length();
    if (len < 1e-5)
      return Vector2D(0, 0);
    return Vector2D(x / len, y / len);
  }

  // Mengembalikan bearing angle dalam derajat (-180 sampai 180)
  double angleDeg() const { return std::atan2(y, x) * 180.0 / M_PI; }

  // Normalisasi sudut agar selalu dalam rentang [-180, 180] derajat
  static double normalizeAngle(double angleDeg) {
    while (angleDeg > 180.0)
      angleDeg -= 360.0;
    while (angleDeg <= -180.0)
      angleDeg += 360.0;
    return angleDeg;
  }

  // Kalkulasi perbedaan sudut relatif dari sudut hadap saat ini ke titik target
  static double calculateBearing(const Vector2D &from, double currentHeadingDeg,
                                 const Vector2D &to) {
    Vector2D diff = to - from;
    double targetAngle = diff.angleDeg();
    return normalizeAngle(targetAngle - currentHeadingDeg);
  }
};

#endif // VECTOR2D_H
