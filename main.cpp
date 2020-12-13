#include <iostream>
#include <istream>
#include <cassert>

#include "game.h"
#include "legalMovesInPosition.h"

void output(const Game &g) {
    std::cout << g << ": ";
}

std::string read() {
    std::string input;
	getline(std::cin, input);
    return input;
}

Game* previous(Game* g) {
    if (g->previous == nullptr)
        throw Exception("There is no previous position to go to");

    Game* old = g;

    g = g->previous;
    old->previous = nullptr;
    delete old;

    return g;
}

Move parse(std::string input, const Game &g) {
    const Position p = g.position();

    if (input.compare("O-O") == 0) {
        return LegalMovesInPosition(p).castling(g.currentPlayer(), Piece::KING);
    }

    if (input.compare("O-O-O") == 0)
        return LegalMovesInPosition(p).castling(g.currentPlayer(), Piece::QUEEN);

    if (input.length() != 5 && input.length() != 7)
        throw Exception(std::to_string(input.length()) + ". Invalid input. Example: \'e2 e4\'");

    Square orig = Square(input[0], input[1] - '0');
    Square dest = Square(input[3], input[4] - '0');

    if (input.length() == 7)
        return LegalMovesInPosition(p).promote(orig, dest, Piece::parseType(input[6]));

    if  ((orig.x == dest.x+1 || orig.x == dest.x-1) &&
        (p.get(orig)->type == Piece::PAWN && p.get(dest) == nullptr))
            return LegalMovesInPosition(p).enpassent(orig, dest);

    return Move(orig, dest);
}

int main() {
    Game* g = new Game();

    while (true) {
        try {
            output(g);
            std::string input = read();

            if (input.compare("z") == 0)
                g = previous(g);

            if (input.compare("q") == 0)
                return 0;

            else g->move(parse(input, g));
        } catch(const Exception &e) {
            std::cout << e.what() << std::endl;
        }
    }
}