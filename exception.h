#pragma once

#include <string>

class Exception {
    public:
        Exception(const std::string& message = "") : message(message) {}
        const std::string what() const { return message; }
    private:
        const std::string message;
};