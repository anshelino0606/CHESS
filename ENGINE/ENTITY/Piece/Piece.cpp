//
// Created by Anhelina Modenko on 11.09.2023.
//

#include "Piece.h"


Piece::Piece(char symbol, Color color, Position position, PieceType type, MoveHandler* moveHandler)
    : symbol(symbol), color(color), position(position), type(type), moveHandler(moveHandler) {}

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
        {'k', PieceType::king},
        {'.', PieceType::NONE},
        {'P', PieceType::pawn},
        {'N', PieceType::knight},
        {'B', PieceType::bishop},
        {'R', PieceType::rook},
        {'Q', PieceType::queen},
        {'K', PieceType::king}
};

std::vector<Position> Piece::getLegalMoves(const Board &board, Position currentPos){
    std::vector<Position> legalMoves;

    switch (type) {
        case PieceType::pawn: {
            int forwardDir = (color == Color::white) ? -1 : 1;
            int startingRow = (color == Color::white) ? 6 : 1;


            // Check one square forward
            if (moveHandler->isEmpty(currentPos.getRow() + forwardDir, currentPos.getCol())) {
                legalMoves.push_back(Position(currentPos.getRow() + forwardDir, currentPos.getCol()));

                // Check two squares forward from the starting position
                if (currentPos.getRow() == startingRow &&
                        moveHandler->isEmpty(currentPos.getRow() + 2 * forwardDir, currentPos.getCol())) {
                    legalMoves.push_back(Position(currentPos.getRow() + 2 * forwardDir, currentPos.getCol()));
                }
            }

            // Check for diagonal captures
            for (int colOffset: {-1, 1}) {
                int targetRow = currentPos.getRow() + forwardDir;
                int targetCol = currentPos.getCol() + colOffset;
                if (moveHandler->isValidPosition(targetRow, targetCol) &&
                        moveHandler->isOppositeColor(targetRow, targetCol, color)
                    && board.getPieceAt(Position(targetRow, targetCol))->getType() != PieceType::NONE) {
                    legalMoves.push_back(Position(targetRow, targetCol));
                }
            }
            break;
        }
        case PieceType::knight: {
            // Legal moves for knights
            int moves[8][2] = {
                    {-1, -2},
                    {-2, -1},
                    {-2, 1},
                    {-1, 2},
                    {1,  -2},
                    {2,  -1},
                    {2,  1},
                    {1,  2}
            };

            for (int i = 0; i < 8; ++i) {
                int targetRow = currentPos.getRow() + moves[i][0];
                int targetCol = currentPos.getCol() + moves[i][1];

                if (moveHandler->isValidPosition(targetRow, targetCol) &&
                    (moveHandler->isEmpty(targetRow, targetCol) || moveHandler->isOppositeColor(targetRow, targetCol, color))) {
                    legalMoves.push_back(Position(targetRow, targetCol));
                }
            }
            break;

        }
        case PieceType::bishop: {
            int directions[4][2] = {
                    {-1, -1},
                    {-1, 1},
                    {1,  -1},
                    {1,  1}
            };

            for (int i = 0; i < 4; ++i) {
                int dr = directions[i][0];
                int dc = directions[i][1];
                int targetRow = currentPos.getRow() + dr;
                int targetCol = currentPos.getCol() + dc;

                while (moveHandler->isValidPosition(targetRow, targetCol)) {
                    if (moveHandler->isEmpty(targetRow, targetCol)) {
                        legalMoves.push_back(Position(targetRow, targetCol));
                    } else {
                        if (moveHandler->isOppositeColor(targetRow, targetCol, color)) {
                            legalMoves.push_back(Position(targetRow, targetCol));
                        }
                        break; // Stop further movement in this direction
                    }
                    targetRow += dr;
                    targetCol += dc;
                }
            }
            break;
        }
        case PieceType::rook: {
            int directions[4][2] = {
                    {-1, 0},
                    {1,  0},
                    {0,  -1},
                    {0,  1}
            };

            for (int i = 0; i < 4; ++i) {
                int dr = directions[i][0];
                int dc = directions[i][1];
                int targetRow = currentPos.getRow() + dr;
                int targetCol = currentPos.getCol() + dc;

                while (moveHandler->isValidPosition(targetRow, targetCol)) {
                    if (moveHandler->isEmpty(targetRow, targetCol)) {
                        legalMoves.push_back(Position(targetRow, targetCol));
                    } else {
                        if (moveHandler->isOppositeColor(targetRow, targetCol, color)) {
                            legalMoves.push_back(Position(targetRow, targetCol));
                        }
                        break; // Stop further movement in this direction
                    }
                    targetRow += dr;
                    targetCol += dc;
                }
                break;
            }
        }
        case PieceType::queen: {
            int directions[8][2] = {
                    {-1, 0}, {1, 0},
                    {0, -1}, {0, 1},
                    {-1, -1}, {-1, 1},
                    {1, -1}, {1, 1}
            };

            for (int i = 0; i < 8; ++i) {
                int dr = directions[i][0];
                int dc = directions[i][1];
                int targetRow = currentPos.getRow() + dr;
                int targetCol = currentPos.getCol() + dc;

                while (moveHandler->isValidPosition(targetRow, targetCol)) {
                    if (moveHandler->isEmpty(targetRow, targetCol)) {
                        legalMoves.push_back(Position(targetRow, targetCol));
                    } else {
                        if (moveHandler->isOppositeColor(targetRow, targetCol, color)) {
                            legalMoves.push_back(Position(targetRow, targetCol));
                        }
                        break; // Stop further movement in this direction
                    }
                    targetRow += dr;
                    targetCol += dc;
                }
            }
            break;
        }
        case PieceType::king: {
            int directions[8][2] = {
                    {-1, 0}, {1, 0},
                    {0, -1}, {0, 1},
                    {-1, -1}, {-1, 1},
                    {1, -1}, {1, 1}
            };

            for (int i = 0; i < 8; ++i) {
                int dr = directions[i][0];
                int dc = directions[i][1];
                int targetRow = currentPos.getRow() + dr;
                int targetCol = currentPos.getCol() + dc;

                if (moveHandler->isValidPosition(targetRow, targetCol)) {
                    if (moveHandler->isEmpty(targetRow, targetCol) ||
                        moveHandler->isOppositeColor(targetRow, targetCol, color)) {
                        legalMoves.push_back(Position(targetRow, targetCol));
                    }
                }
            }
            break;
        }

        default:
            break;
    }
    return legalMoves;
}

Piece::Piece(const Piece &other) {
    this->symbol = other.symbol;
    this->color = other.color;
    this->position = other.position;
    this->type = other.type;
    this->moveHandler = other.moveHandler;

}

Piece &Piece::operator=(const Piece &other) {
    this->symbol = other.symbol;
    this->color = other.color;
    this->position = other.position;
    this->type = other.type;
    this->moveHandler = other.moveHandler;
    return *this;
}
