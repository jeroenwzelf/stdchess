#pragma once

#include "position.h"

struct Move {
    struct Type {
        Type() : special(false), piece(Piece::QUEEN) {}

        bool special;
        Piece::Type piece;

        protected: friend class LegalMovesInPosition;
            Type(Piece::Type piece) : special(true), piece(piece) {}
    };

    Move(const Square& orig, const Square& dest)
        : orig(orig), dest(dest), type(Type()) {}
    Move(const Square& orig, const Square& dest, Move::Type type)
        : orig(orig), dest(dest), type(type) {}

    const Square orig, dest;
    Move::Type type;

    struct IllegalMoveException : public Exception {
        IllegalMoveException(std::string message) : Exception(message) {}
    };
};

std::ostream& operator<<(std::ostream& os, const Move& p) {
    return os << p.orig << " -> " << p.dest;
}