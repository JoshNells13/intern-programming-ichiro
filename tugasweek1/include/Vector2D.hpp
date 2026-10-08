#ifndef VECTOR2D_HPP
#define VECTOR2D_HPP

#include <cmath>

const double PI = 3.14159265358979323846;

struct Vector2D {
    double x;
    double y;

    Vector2D() : x(0.0), y(0.0) {}
    Vector2D(double x, double y) : x(x), y(y) {}

    Vector2D operator+(const Vector2D& o) const { return Vector2D(x + o.x, y + o.y); }
    Vector2D operator-(const Vector2D& o) const { return Vector2D(x - o.x, y - o.y); }
    Vector2D operator*(double s) const { return Vector2D(x * s, y * s); }

    double length() const { return std::sqrt(x * x + y * y); }
    double distanceTo(const Vector2D& o) const { return (*this - o).length(); }

    Vector2D normalized() const {
        double len = length();
        return (len < 1e-5) ? Vector2D(0, 0) : Vector2D(x / len, y / len);
    }

    double angleDeg() const {
        return std::atan2(y, x) * 180.0 / PI;
    }

    static double normalizeAngle(double deg) {
        while (deg > 180.0) deg -= 360.0;
        while (deg <= -180.0) deg += 360.0;
        return deg;
    }

    static double calculateBearing(const Vector2D& from, double heading, const Vector2D& to) {
        Vector2D diff = to - from;
        return normalizeAngle(diff.angleDeg() - heading);
    }
};

#endif
