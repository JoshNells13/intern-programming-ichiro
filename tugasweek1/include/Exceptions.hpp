#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP

#include <exception>
#include <string>

class RobotException : public std::exception {
protected:
    std::string message;
public:
    RobotException(const std::string& msg) : message(msg) {}
    const char* what() const noexcept override {
        return message.c_str();
    }
};

class InvalidKickException : public RobotException {
public:
    InvalidKickException(const std::string& msg = "Bola tidak berada di depan robot untuk ditendang")
        : RobotException(msg) {}
};

class OutOfBoundsException : public RobotException {
public:
    OutOfBoundsException(const std::string& msg = "Posisi keluar dari batas lapangan")
        : RobotException(msg) {}
};

#endif
