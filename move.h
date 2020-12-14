#pragma once

#include "position.h"

/*
 * Represents a move on a chessboard. Sometimes, a move will involve moving more 
 * than one more piece (like castling and taking en passant). These special cases 
 * are contained in Move::Type type.
 * 
 * @param orig: The Square of the piece to move.
 * @param dest: The destination Square for the piece.
 * @param type: An indication of a special move like castling or promoting.
*/
struct Move {
    /*
     * Whether a move is a special move. It can be disregarded if @param special 
     * is false. If {piece} is Piece::PAWN, the move is en passant. If 
     * {piece} is Piece::King, castling is meant. Otherwise, the move is a 
     * pawn promotion.
     * 
     * @param special:  Whether the type should be disregarded or not.
     * @param piece:    Used to indicate castling (with Piece::KING), en passant 
     *                  (with Piece::PAWN), or promoting.
    */
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
        IllegalMoveException(const std::string& reason) : Exception(reason) {}
    };
};

std::ostream& operator<<(std::ostream& os, const Move& p) {
    return os << p.orig << " -> " << p.dest;
}