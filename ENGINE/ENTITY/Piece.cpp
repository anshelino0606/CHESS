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

std::vector<Position> Piece::getLegalMoves(const Board &board, Position currentPos) {
    std::vector<Position> legalMoves;

    if (board.getPieceAt(currentPos)->getSymbol() == 'P') {
        if (currentPos.getRow() == 6) {
            if (board.isEmpty(currentPos.getRow()-1, currentPos.getCol())) {
                legalMoves.push_back(Position(currentPos.getRow() - 1, currentPos.getCol()));
                if (board.isEmpty(currentPos.getRow()-2, currentPos.getCol())) {
                    legalMoves.push_back(Position(currentPos.getRow() - 2, currentPos.getCol()));
                }
            }
        } else {
            if (board.isEmpty(currentPos.getRow()-1, currentPos.getCol())) {
                legalMoves.push_back(Position(currentPos.getRow() - 1, currentPos.getCol()));
            }
        }
        if (board.isEmpty(currentPos.getRow()-1, currentPos.getCol())) {
            legalMoves.push_back(Position(currentPos.getRow() - 1, currentPos.getCol()));
        }
    }

    return legalMoves;
}
