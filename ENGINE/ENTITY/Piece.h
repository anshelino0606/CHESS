//
// Created by Anhelina Modenko on 11.09.2023.
//

#ifndef CHESS_PIECE_H
#define CHESS_PIECE_H

#include "Position/Position.hpp"
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

    std::vector<Position> getLegalMoves(const Board& board, Position currentPos) const;

    PieceType getType() const {
        return type;
    }

    char getSymbol() const {
        return symbol;
    }

    char setSymbol(char symbol) {
        this->symbol = symbol;
    }

    Color getColor() const {
        return color;
    }

    Position getPosition() const {
        return position;
    }

    void setPosition(Position position) {
        this->position = position;
    }

    static std::unordered_map<char, PieceType> pieceTypeMap;


    ~Piece();

private:
    char symbol;
    Position position;
    PieceType type;
    Color color;
};


#endif //CHESS_PIECE_H
