//
// Created by Anhelina Modenko on 25.09.2023.
//

#include "CheckDetector.h"

CheckDetector::CheckDetector(Board &board) : board(board) {}

std::vector<Position> CheckDetector::getLegalMoves(const Board &board, Position currentPos) {
    std::vector<Position> legalMoves;
    Piece* piece = board.getPieceAt(currentPos);
    if (piece != nullptr) {
        legalMoves = piece->getLegalMoves(board, currentPos);
    }
    return legalMoves;
}

bool CheckDetector::isMoveLegal(const Board &board, Position currentPos, Position newPos) {
    std::vector<Position> legalMoves = getLegalMoves(board, currentPos);
    for (auto move : legalMoves) {
        if (move == newPos) {
            return true;
        }
    }
    return false;
}

bool CheckDetector::isKingAttacked(Color currentPlayerColor) {
    Position kingPos;
    // get current player's king position
    for (int i = 0; i < NB_SQ / 8; ++i) {
        for (int j = 0; j < NB_SQ / 8; ++j) {
            Piece *piece = board.getPieceAt(Position(i, j));
            if (piece != nullptr && piece->getType() == PieceType::king && piece->getColor() == currentPlayerColor) {
                kingPos = piece->getPosition();
            }
        }
    }
    Color opponentColor = currentPlayerColor == Color::white ? Color::black : Color::white;
    std::vector<Position> opponentMoves;
    // get opponent's legal moves
    for (int i = 0; i < NB_SQ / 8; ++i) {
        for (int j = 0; j < NB_SQ / 8; ++j) {
            Piece *piece = board.getPieceAt(Position(i, j));
            if (piece != nullptr && piece->getColor() == opponentColor && board.board[i*8 + j] != '.') {
                std::vector<Position> pieceMoves = piece->getLegalMoves(board, piece->getPosition());
                opponentMoves.insert(opponentMoves.end(), pieceMoves.begin(), pieceMoves.end());
            }
        }
    }
    for (auto move : opponentMoves) {
        if (move == kingPos) {
            return true;
        }
    }
    return false;
}

Position CheckDetector::getOpponentKingPosition(Color currentPlayerColor) {
    Color opponentColor = currentPlayerColor == Color::white ? Color::black : Color::white;
    for (int i = 0; i < NB_SQ / 8; ++i) {
        for (int j = 0; j < NB_SQ / 8; ++j) {
            Piece *piece = board.getPieceAt(Position(i, j));
            if (piece != nullptr && piece->getType() == PieceType::king && piece->getColor() == opponentColor) {
                return piece->getPosition();
            }
        }
    }
}

bool CheckDetector::isCheck(Color currentPlayerColor) {
    return isKingAttacked(currentPlayerColor);
}

bool CheckDetector::isCheckmate(Color currentPlayerColor) {
    if (!isCheck(currentPlayerColor)) {
        return false;
    }
    for (int i = 0; i < NB_SQ / 8; ++i) {
        for (int j = 0; j < NB_SQ / 8; ++j) {
            Piece *piece = board.getPieceAt(Position(i, j));
            if (piece != nullptr && piece->getColor() == currentPlayerColor) {
                std::vector<Position> pieceMoves = piece->getLegalMoves(board, piece->getPosition());
                for (auto move : pieceMoves) {
                    if (isMoveLegal(board, piece->getPosition(), move)) {
                        return false;
                    }
                }
            }
        }
    }
    return true;
}

bool CheckDetector::isPin(Color currentPlayerColor, Position from, Position to) {
    Board tempBoard = board;
    tempBoard.moveHandler->makeMove(from, to);
    return isKingAttacked(currentPlayerColor);
}


