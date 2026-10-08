#include "ConfigLoader.hpp"
#include <fstream>
#include <sstream>

SimConfig ConfigLoader::loadFromFile(const std::string& filename) {
    SimConfig config;
    std::ifstream file(filename);
    if (!file.is_open()) {
        return config;
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty() || line[0] == '#') continue;

        size_t eqPos = line.find('=');
        if (eqPos != std::string::npos) {
            std::string key = line.substr(0, eqPos);
            std::string val = line.substr(eqPos + 1);

            try {
                if (key == "ROBOT_X") config.robotX = std::stod(val);
                else if (key == "ROBOT_Y") config.robotY = std::stod(val);
                else if (key == "ROBOT_ORIENTATION") config.robotOrientation = std::stod(val);
                else if (key == "BALL_X") config.ballX = std::stod(val);
                else if (key == "BALL_Y") config.ballY = std::stod(val);
                else if (key == "MAX_TICKS") config.maxTicks = std::stoi(val);
            } catch (...) {
                // Gunakan default value jika format salah
            }
        }
    }

    return config;
}
