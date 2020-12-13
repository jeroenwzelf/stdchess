#pragma once

#include "move.h"

/*
 * Special moves for @position are defined here, and it could provide as
 * a base for implementing the other legal moves for specific pieces.
*/
struct LegalMovesInPosition {
    LegalMovesInPosition(const Position& position) : position(position) {}
    const Position position;

    Move castling(Piece::Color color, Piece::Type side) const;
    Move enpassent(const Square& orig, const Square& dest) const;
    Move promote(const Square& orig, const Square& dest, Piece::Type type) const;
};

Move LegalMovesInPosition::castling(Piece::Color color, Piece::Type side) const {
    unsigned y = (bool)color ? 0 : 7;
    unsigned dest_x = (side == Piece::KING) ? 6 : 2;

    Square orig = Square((unsigned)4, y);
    Square dest = Square(dest_x, y);

    if (position.get(orig)->type != Piece::KING)
        throw Move::IllegalMoveException("You can't castle (your king has already moved)");

    for (unsigned x = 4; x != dest_x; (bool)color ? ++x : --x)
        if (position.get(Square(x, y)) != nullptr)
            throw Move::IllegalMoveException("You can't castle through other pieces");

    return Move(orig, dest, Move::Type(Piece::KING));
}

Move LegalMovesInPosition::enpassent(const Square& orig, const Square& dest) const {
    Piece* pawn = position.get(orig);
    Piece::Color player = pawn->color;

    Square enemy_pawn_orig = Square(dest.x, dest.y + ((bool)player ? 1 : -1));
    Piece* enemy_pawn = position.get(enemy_pawn_orig);

    if (pawn->type != Piece::PAWN)
        throw Move::IllegalMoveException("Only pawns can take en passent");
    
    if (enemy_pawn->type != Piece::PAWN)
        throw Move::IllegalMoveException("You can only take other pawns en passent");

    if (orig.x != dest.x+1 && orig.x != dest.x-1)
        throw Move::IllegalMoveException("Taking en passent means taking a pawn");

    if (orig.y != (bool)player ? 4 : 3)
        throw Move::IllegalMoveException("Pawn is not on the correct rank to take en passent");

    return Move(orig, dest, Move::Type(Piece::PAWN));
}

Move LegalMovesInPosition::promote(const Square& orig, const Square& dest, Piece::Type type) const {
    Piece* pawn = position.get(orig);
    Piece::Color player = pawn->color;

    if (pawn->type != Piece::PAWN)
        throw Move::IllegalMoveException("Only pawns can promote");

    if (dest.y != ((bool)player) ? 7 : 0)
        throw Move::IllegalMoveException("Pawns can only promote at the end of the board");

    return Move(orig, dest, Move::Type(type));
}