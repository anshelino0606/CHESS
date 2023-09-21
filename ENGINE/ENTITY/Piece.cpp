//
// Created by Anhelina Modenko on 11.09.2023.
//

#include "Piece.h"


Piece::Piece(char symbol, Color color, Position position, PieceType type)
    : symbol(symbol), color(color), position(position), type(type) {}

Piece::~Piece() {
    delete this;
}



