//
// Created by Anhelina Modenko on 11.09.2023.
//

#ifndef CHESS_PIECE_H
#define CHESS_PIECE_H

#include "Position/Position.hpp"
#include <vector>

class Board;
enum class Color;

class Piece {
public:

    Piece(char symbol, Color color, Position position);

    virtual std::vector<Position> getLegalMoves(const Board& board, Position currentPos) const = 0;

    virtual ~Piece();


private:
    char symbol;
    Color color;
    Position position;

};


#endif //CHESS_PIECE_H
