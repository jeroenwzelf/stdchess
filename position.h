#pragma once

#include <sstream>

#include "piece.h"
#include "square.h"

/*
 * A simple chessboard containing chesspieces. A new Position is 
 * instantiated with the default initial chessposition. 
 * Player::Color perspective is used for printing the board the 
 * right side up for either White or Black.
 * 
 * @param p: A position to copy the board from.
 *                      
*/
struct Position {
        Position();
        Position(const Position& p);

        Piece* get(const Square& square) const;

        void place(const Piece& piece, const Square& dest);
        void remove(const Square& square);
        void move(const Square& orig, const Square& dest);

        Piece* board[8][8];
        Piece::Color perspective = Piece::Color::WHITE;
};

Position::Position() {
        unsigned pieces_row = 0, pawns_row = 1;
        Piece::Color color = Piece::Color::WHITE;

        for (unsigned player = 0; player < 2; ++player) {
                for (unsigned x = 0; x < 8; ++x) {
                        Piece::Type piece;
                        switch (x) {
                                case 0: case 7: piece = Piece::ROOK; break;
                                case 2: case 5: piece = Piece::BISHOP; break;
                                case 1: case 6: piece = Piece::KNIGHT; break;
                                case 3: piece = Piece::QUEEN; break;
                                case 4: piece = Piece::KING; break;
                        }
                        board[pieces_row][x] = new Piece(piece, color);
                        board[pawns_row][x] = new Piece(Piece::PAWN, color);
                }
                pieces_row = 7; pawns_row = 6;
                color = Piece::Color::BLACK;
        }

        for (unsigned y = 2; y < 6; ++y) {
                for (unsigned x = 0; x < 8; ++x) {
                        board[y][x] = nullptr;
                }
        }
}

Position::Position(const Position& p) {
        for (unsigned y = 0; y < 8; ++y) {
                for (unsigned x = 0; x < 8; ++x) {
                        Piece* piece = p.board[y][x];
                        board[y][x] = piece ? new Piece(piece) : nullptr;
                }
        }
}

Piece* Position::get(const Square& square) const {
        return board[square.y][square.x];
}

void Position::place(const Piece& piece, const Square& dest) {
        remove(dest);
        board[dest.y][dest.x] = new Piece(piece);
}

void Position::remove(const Square& square) {
        delete get(square);
        board[square.y][square.x] = nullptr;
}

void Position::move(const Square& orig, const Square& dest) {
        delete get(dest);
        board[dest.y][dest.x] = get(orig);
        board[orig.y][orig.x] = nullptr;
}

std::ostream& operator<<(std::ostream& os, const Position& p) {
        auto row = [&] (std::ostream& os, const Position& p, const unsigned &y) -> void {
                for (unsigned x=0; x < 8; ++x) {
                        if (p.board[y][x] == nullptr) os << (((y + x) % 2 == 0) ? "\u25A0" : "\u25A1");
                        else os << *p.board[y][x];

                        os << " ";
                }
                os << y+1 << std::endl;
        };

        if (p.perspective == Piece::Color::WHITE) for (unsigned y = 7; y < 8; --y) row(os, p, y);
        else for (unsigned y = 0; y < 8; ++y) row(os, p, y);

        return os << "a b c d e f g h";
}