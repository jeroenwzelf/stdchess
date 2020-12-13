#pragma once

#include <string>
#include "exception.h"

class Square {
        public:
                Square(char x, unsigned y) : Square((unsigned)(std::tolower(x) - 'a'), y-1) {}
                Square(unsigned x, unsigned y);

                const unsigned x, y;
                
                char x_char() const { return x + 'a'; }
                char y_char() const { return y + '0'; }
                std::string toString() const;

                struct OutOfBoundsException : public Exception {
                        OutOfBoundsException(std::string message) : Exception(message) {}
                };
};

Square::Square(unsigned x, unsigned y) : x(x), y(y) {
        if (x < 0 || y < 0 || x > 7 || y > 7)
                throw OutOfBoundsException("The square " + toString() + " does not exist!");
}

std::string Square::toString() const {
        return std::string() + x_char() + y_char();
}

std::ostream& operator<<(std::ostream& os, const Square& s) {
        return os << s.toString();
}