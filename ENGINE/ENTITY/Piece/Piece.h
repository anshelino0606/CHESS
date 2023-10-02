//
// Created by Anhelina Modenko on 11.09.2023.
//

#ifndef CHESS_PIECE_H
#define CHESS_PIECE_H

#include "ENGINE/ENTITY/Position/Position.hpp"
#include "ENGINE/ENTITY/Board/Board.h"
#include <vector>
#include <map>

class MoveHandler;
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
    Piece(char symbol, Color color, Position position, PieceType type, MoveHandler* moveHandler);
    Piece(const Piece& other);

    virtual std::vector<Position> getLegalMoves(const Board& board, Position currentPos);

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

    Piece& operator=(const Piece& other);

    virtual ~Piece();

private:
    char symbol;
    Position position;
    PieceType type;
    Color color;
    MoveHandler* moveHandler;
};


#endif //CHESS_PIECE_H
