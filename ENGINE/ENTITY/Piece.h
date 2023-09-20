//
// Created by Anhelina Modenko on 11.09.2023.
//

#ifndef CHESS_PIECE_H
#define CHESS_PIECE_H

#include "Position/Position.hpp"
#include <vector>

class Board;
enum class Color;

enum class PieceType {
    pawn,
    knight,
    bishop,
    rook,
    queen,
    king
};

class Piece {
public:

    Piece(char symbol, Color color, Position position, PieceType type);

    virtual std::vector<Position> getLegalMoves(const Board& board, Position currentPos) const = 0;

    virtual ~Piece();

private:
    char symbol;
    Position position;
    PieceType type;

protected:
    Color color;
};


#endif //CHESS_PIECE_H
