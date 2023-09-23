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

std::vector<Position> Piece::getLegalMoves(const Board &board, Position currentPos){
    std::vector<Position> legalMoves;

    int forwardDir = (color == Color::white) ? -1 : 1;
    int startingRow = (color == Color::white) ? 6 : 1;

    // Check one square forward
    if (board.isEmpty(currentPos.getRow() + forwardDir, currentPos.getCol())) {
        legalMoves.push_back(Position(currentPos.getRow() + forwardDir, currentPos.getCol()));

        // Check two squares forward from the starting position
        if (currentPos.getRow() == startingRow &&
            board.isEmpty(currentPos.getRow() + 2 * forwardDir, currentPos.getCol())) {
            legalMoves.push_back(Position(currentPos.getRow() + 2 * forwardDir, currentPos.getCol()));
        }
    }

    // Check for diagonal captures
    for (int colOffset : {-1, 1}) {
        int targetRow = currentPos.getRow() + forwardDir;
        int targetCol = currentPos.getCol() + colOffset;
        if (board.isValidPosition(targetRow, targetCol) &&
            board.isOpponent(targetRow, targetCol, color)) {
            legalMoves.push_back(Position(targetRow, targetCol));
        }
    }
    return legalMoves;
}
