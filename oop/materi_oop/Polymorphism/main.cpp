#include <iostream>
#include <vector>
#include <memory>

class Robot {
public:
    virtual ~Robot() = default;

    virtual void performAction() const {
        std::cout << "Robot melakukan aksi umum.\n";
    }
};

class StrikerRobot : public Robot {
public:
    void performAction() const override {
        std::cout << "Striker berlari dan menembak ke gawang musuh!\n";
    }
};

class DefenderRobot : public Robot {
public:
    void performAction() const override {
        std::cout << "Defender memblokir pergerakan lawan!\n";
    }
};

class RefereeRobot : public Robot {
public:
    void performAction() const override {
        std::cout << "Referee meniup peluit tanda pelanggaran!\n";
    }
};

int main() {
    // Alur: Simpan berbagai objek child ke dalam vector pointer base class
    std::vector<std::unique_ptr<Robot>> team;
    team.push_back(std::make_unique<StrikerRobot>());
    team.push_back(std::make_unique<DefenderRobot>());
    team.push_back(std::make_unique<RefereeRobot>());

    // Eksekusi fungsi virtual secara dinamis saat runtime (polimorfisme)
    for (const auto& member : team) {
        member->performAction();
    }

    return 0;
}
