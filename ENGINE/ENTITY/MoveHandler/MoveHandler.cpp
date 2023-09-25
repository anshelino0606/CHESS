//
// Created by Anhelina Modenko on 25.09.2023.
//

#include "MoveHandler.h"
#include "../Board.h"

MoveHandler::MoveHandler(Board &board)
    : board(board) {}

bool MoveHandler::makeMove(Position from, Position to) {
    if (!isValidPosition(from.getRow(), from.getCol()) || !isValidPosition(to.getRow(), to.getCol())) {
        return false;
    }

    Piece* piece = board.getPieceAt(from);
    if (piece == nullptr)
        return false;

    Piece* capturedPiece = board.getPieceAt(to);
    if (capturedPiece != nullptr) {
        capturedPiece->setPosition(Position(-1, -1));
    }

    piece->setPosition(to);
    board.board[to.getRow() * 8 + to.getCol()] = board.board[from.getRow() * 8 + from.getCol()];
    board.board[from.getRow() * 8 + from.getCol()] = '.';

    board.selectedPiece = nullptr;
    board.rowSelected = -1;
    board.colSelected = -1;

    return false;
}

bool MoveHandler::isOppositeColor(int row, int col, Color currentPlayerColor) const {
    if (isEmpty(row, col))
        return false;

    return currentPlayerColor == Color::black && isupper(board.board[row * 8 + col]) &&
           board.board[row * 8 + col] != '.'
           || currentPlayerColor == Color::white && islower(board.board[row * 8 + col]) &&
              board.board[row * 8 + col] != '.';
}

bool MoveHandler::isValidPosition(int row, int col) const {
    return row >= 0 && row < 8 && col >= 0 && col < 8;
}


bool MoveHandler::isEmpty(int row, int col) const {
    return board.board[row * 8 + col] == '.';
}