#include <iostream>
#include <istream>
#include <cassert>

#include "game.h"
#include "legalMovesInPosition.h"

void output(const Game &g) {
    std::cout << g << ": ";
}

std::string input() {
    std::string input;
	getline(std::cin, input);
    return input;
}

Move parse(std::string input, const Game &g) {
    if (input.compare("O-O") == 0) {
        g.position();
        return LegalMovesInPosition(g.position()).castling(g.currentPlayer(), Piece::KING);
    }

    if (input.compare("O-O-O") == 0)
        return LegalMovesInPosition(g.position()).castling(g.currentPlayer(), Piece::QUEEN);

    if (input.length() != 5 && input.length() != 7)
        throw Exception(std::to_string(input.length()) + ". Invalid input. Example: \'e2 e4\'");

    Square orig = Square(input[0], input[1] - '0');
    Square dest = Square(input[3], input[4] - '0');

    if (input.length() == 7)
        return LegalMovesInPosition(g.position()).promote(orig, dest, Piece::parseType(input[6]));

    if  ((orig.x == dest.x+1 || orig.x == dest.x-1) &&
        (g.getPiece(orig)->type == Piece::PAWN && g.getPiece(dest) == nullptr))
            return LegalMovesInPosition(g.position()).enpassent(orig, dest);

    return Move(orig, dest);
}

int main() {
    Game g;

    while (true) {
        output(g);

        try {
            g.move(parse(input(), g));
        } catch(const Exception &e) {
            std::cout << e.what() << std::endl;
        }
    }
}