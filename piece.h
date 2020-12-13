#pragma once

#include <iostream>
#include <sstream>
#include <string>

#include "exception.h"

struct Piece {
    enum Type {PAWN, ROOK, BISHOP, KNIGHT, KING, QUEEN } type;
    const enum class Color : bool { WHITE=true, BLACK=false } color;

    Piece(Type type, Color color) : type(type), color(color) {}
    Piece(const Piece *p) : type(p->type), color(p->color) {}

    static Type parseType(const char& type);
};

Piece::Type Piece::parseType(const char& type) {
    switch (std::toupper(type)) {
        case 'P': return Piece::PAWN;
        case 'R': return Piece::ROOK;
        case 'B': return Piece::BISHOP;
        case 'N': return Piece::KNIGHT;
        case 'K': return Piece::KING;
        case 'Q': return Piece::QUEEN;
    }
    throw Exception(type + " can not be parsed as a valid piece.");
}

std::ostream& operator<<(std::ostream& os, const Piece& p) {
    switch (p.type) {
        case Piece::KING:   return os << ((bool)p.color ? "\u265A" : "\u2654");
        case Piece::QUEEN:  return os << ((bool)p.color ? "\u265B" : "\u2655");
        case Piece::ROOK:   return os << ((bool)p.color ? "\u265C" : "\u2656");
        case Piece::BISHOP: return os << ((bool)p.color ? "\u265D" : "\u2657");
        case Piece::KNIGHT: return os << ((bool)p.color ? "\u265E" : "\u2658");
        case Piece::PAWN:   return os << ((bool)p.color ? "\u265F" : "\u2659");
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, const Piece::Color& c) {
    return os << ((bool) c ? "White" : "Black");
}