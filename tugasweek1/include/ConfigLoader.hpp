#ifndef CONFIG_LOADER_HPP
#define CONFIG_LOADER_HPP

#include <string>

struct SimConfig {
    double robotX = -1.5;
    double robotY = -0.5;
    double robotOrientation = 90.0;
    double ballX = 0.0;
    double ballY = 0.5;
    int maxTicks = 30;
};

class ConfigLoader {
public:
    static SimConfig loadFromFile(const std::string& filename);
};

#endif
