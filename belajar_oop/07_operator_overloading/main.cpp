#include <iostream>

class Vector2D {
public:
    double x;
    double y;

    Vector2D(double xVal = 0.0, double yVal = 0.0) : x(xVal), y(yVal) {}

    // Overload operator +
    Vector2D operator+(const Vector2D& other) const {
        return Vector2D(x + other.x, y + other.y);
    }

    // Overload operator ==
    bool operator==(const Vector2D& other) const {
        return (x == other.x) && (y == other.y);
    }

    // Overload operator <<
    friend std::ostream& operator<<(std::ostream& os, const Vector2D& vec) {
        os << "(" << vec.x << ", " << vec.y << ")";
        return os;
    }
};

int main() {
    // Alur: Buat 2 vektor -> jumlahkan dengan '+' -> cetak dengan '<<' -> uji '=='
    Vector2D posRobot(10.5, 20.0);
    Vector2D velocity(2.0, -1.5);

    Vector2D newPos = posRobot + velocity;

    std::cout << "Posisi Awal   : " << posRobot << "\n";
    std::cout << "Kecepatan     : " << velocity << "\n";
    std::cout << "Posisi Baru   : " << newPos << "\n";

    Vector2D target(12.5, 18.5);
    if (newPos == target) {
        std::cout << "Robot telah mencapai posisi target!\n";
    }

    return 0;
}
