//
// Created by Anhelina Modenko on 11.09.2023.
//

#include "Piece.h"


Piece::Piece(char symbol, Color color, Position position, PieceType type)
    : symbol(symbol), color(color), position(position), type(type) {}

Piece::~Piece() {
    delete this;
}

Piece::Piece() : symbol('.'), color(), position(Position(0, 0)), type(PieceType::NONE) {}



std::unordered_map<char, PieceType> Piece::pieceTypeMap = {
        {'p', PieceType::pawn},
        {'n', PieceType::knight},
        {'b', PieceType::bishop},
        {'r', PieceType::rook},
        {'q', PieceType::queen},
        {'k', PieceType::king}
};