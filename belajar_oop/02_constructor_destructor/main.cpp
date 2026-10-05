#include <iostream>
#include <string>

class Robot {
private:
    std::string name;
    int id;

public:
    Robot() : name("Unknown"), id(0) {
        std::cout << "[Constructor Default] Robot baru dibuat!\n";
    }

    Robot(std::string rName, int rId) : name(rName), id(rId) {
        std::cout << "[Constructor Param] Robot " << name << " (ID: " << id << ") dibuat!\n";
    }

    Robot(const Robot& other) : name(other.name + "_Clone"), id(other.id + 100) {
        std::cout << "[Copy Constructor] Clone dari " << other.name << " dibuat!\n";
    }

    ~Robot() {
        std::cout << "[Destructor] Robot " << name << " dihapus dari memori.\n";
    }

    void print() const {
        std::cout << "-> Info: " << name << " [ID: " << id << "]\n";
    }
};

int main() {
    // Alur 1: Inisialisasi lewat default, parameterized, & copy constructor
    Robot r1;
    Robot r2("Ichiro-Striker", 7);
    Robot r3 = r2;

    r1.print();
    r2.print();
    r3.print();

    // Alur 2: Lifecycle objek di dalam inner scope (destructor dipanggil saat keluar scope)
    {
        Robot rTemp("TempBot", 99);
        rTemp.print();
    }

    return 0;
}
