#pragma once

#include <vector>

#include "move.h"

/*
 * A simple implementation of a chessgame. It keeps track of the current
 * player (White or Black), the amount of moves played, and a game state.
 * 
 * @param g: The game to copy.
*/
class Game {
    public:
        Game();
        // Game(const Game& g)
        //     : previous_move(new Move(*g.previous_move)), previous(g.previous), state(g.state), _position(Position(g._position)) {}
        Game(Game* g)
            : previous_move(g->previous_move ? new Move(*g->previous_move) : nullptr), previous(g->previous), state(g->state), _position(Position(g->_position)) {}

        void move(const Move& m);
        void undo();

        Piece* getPiece(const Square& square) const;
        Position position() const;

        Game* previous = nullptr;
        std::vector<Move*> moves() const;
        Piece::Color currentPlayer() const;

        enum class State { PLAYING } state;

        friend std::ostream& operator<<(std::ostream& os, const Game& p);
    private:
        Position _position;

        Move* previous_move = nullptr;
};

Game::Game() {
    state = State::PLAYING;
}

void Game::move(const Move& move) {
    if (state != State::PLAYING)
        throw Move::IllegalMoveException("The game is not in progress");

    Piece* orig_piece = _position.get(Square(move.orig));

    if (orig_piece == nullptr)
        throw Move::IllegalMoveException("There is no piece to be moved on " + move.orig.toString());

    if (orig_piece->color != currentPlayer())
        throw Move::IllegalMoveException("The current player can not move the piece on " + move.orig.toString());

    previous = new Game(this);
    previous_move = new Move(move);
    _position.move(move.orig, move.dest);

    if (move.type.special) {
        switch (move.type.piece) {
            // Promoting
            case Piece::QUEEN: case Piece::KNIGHT: case Piece::BISHOP: case Piece::ROOK: {
                orig_piece->type = move.type.piece;
                break;
            }
            // Castling
            case Piece::KING: {
                Move rook = (move.orig.x < move.dest.x) ? 
                    Move(Square((unsigned)7, move.dest.y), Square((unsigned)5, move.dest.y)) :  // Kingside castling
                    Move(Square((unsigned)0, move.dest.y), Square((unsigned)3, move.dest.y));   // Queenside castling
                _position.move(rook.orig, rook.dest);
                break;
            }
            // En passant
            case Piece::PAWN: {
                Square enemyPawn = Square(move.dest.x, move.dest.y + ((bool)currentPlayer() ? -1 : 1));
                _position.remove(enemyPawn);
                break;
            }
        }
    }
}

Piece* Game::getPiece(const Square& square) const {
    return _position.get(square);
}

Position Game::position() const {
    return _position;
}

std::vector<Move*> Game::moves() const {
    if (previous == nullptr)
        return std::vector<Move*>();

    std::vector<Move*> moves = previous->moves();
    if (previous_move != nullptr)
        moves.push_back(previous_move);

    return moves;
}

Piece::Color Game::currentPlayer() const {
    return (Piece::Color)(moves().size() % 2 == 0);
}

std::ostream& operator<<(std::ostream& os, const Game& g) {
    return os   << '\r' << "-------------------------------------- MOVE "
                        << g.moves().size() << " (" << g.currentPlayer() << "\'s turn)" << std::endl
                << g._position
                << std::endl;
}

std::ostream& operator<<(std::ostream& os, const std::vector<Move*>& moves) {
    for (unsigned i = 0; i < moves.size(); ++i)
        os << i << ". " << *moves.at(i) << std::endl;
    return os;
}