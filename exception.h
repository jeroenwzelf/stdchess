#pragma once

#include <string>

/*
 * Base Exception class containing a simple exception reason.
*/
class Exception {
    public:
        Exception(const std::string& reason = "") : reason(reason) {}
        const std::string what() const { return reason; }
    private:
        const std::string reason;
};