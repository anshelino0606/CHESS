//
// Created by Anhelina Modenko on 25.09.2023.
//

#include "MoveHandler.h"
#include "ENGINE/ENTITY/Board/Board.h"

Board* helpingBoard = new Board(1000,1000);

MoveHandler::MoveHandler(Board &board)
    : board(board) {
    checkDetector = new CheckDetector(board);
}

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

bool MoveHandler::isMoveLegal(const Board &board, Position currentPos, Position newPos) {
std::vector<Position> legalMoves = board.getPieceAt(currentPos)->getLegalMoves(board, currentPos);

    for (auto move : legalMoves) {
        if (move == newPos) {
            // Make a copy of the board to simulate the move
            Board tempBoard = board;

            // Make a copy of the move handler without modifying the original
            MoveHandler tempMoveHandler = *tempBoard.moveHandler;
            // copy selected piece, and asign different memory address
            tempMoveHandler.board.selectedPiece = tempBoard.getPieceAt(currentPos);

            // Simulate the move on the temporary board
            tempMoveHandler.makeMove(currentPos, newPos);

            // Check if the king is attacked after the move
            if (!checkDetector->isKingAttacked(tempBoard.getPieceAt(currentPos)->getColor())) {
                return true;
            }
        }
    }

    return false;
}

