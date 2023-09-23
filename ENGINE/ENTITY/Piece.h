//
// Created by Anhelina Modenko on 11.09.2023.
//

#ifndef CHESS_PIECE_H
#define CHESS_PIECE_H

#include "Position/Position.hpp"
#include "Board.h"
#include <vector>
#include <map>

class Board;
enum class Color;

enum class PieceType {
    pawn,
    knight,
    bishop,
    rook,
    queen,
    king,
    NONE
};


class Piece {
public:

    Piece();
    Piece(char symbol, Color color, Position position, PieceType type);

    std::vector<Position> getLegalMoves(const Board& board, Position currentPos);

    virtual PieceType getType() const {
        return type;
    }

    virtual char getSymbol() const {
        return symbol;
    }

    virtual char setSymbol(char symbol) {
        this->symbol = symbol;
    }

    virtual Color getColor() const {
        return color;
    }

    virtual Position getPosition() const {
        return position;
    }

    virtual void setPosition(Position position) {
        this->position = position;
    }

    static std::unordered_map<char, PieceType> pieceTypeMap;

    virtual ~Piece();

private:
    char symbol;
    Position position;
    PieceType type;
    Color color;
};


#endif //CHESS_PIECE_H
