//
// Created by Anhelina Modenko on 25.09.2023.
//

#ifndef CHESS_CHECKDETECTOR_H
#define CHESS_CHECKDETECTOR_H

#include "../Board/Board.h"

class CheckDetector {
public:

    /*
     * CONSTRUCTOR
     */
    CheckDetector(Board& board);

    /*
     * FUNCTIONALITY
     */

    /*
     * Checks if the current player is in check
     * @param currentPlayerColor - color of the current player
     */
    bool isCheck(Color currentPlayerColor);

    /*
     * Checks if the current player is in pin
     * @param currentPlayerColor - color of the current player
     * @param from - position of the current player's piece
     * @param to - position of the piece to move
     */
    bool isPin(Color currentPlayerColor, Position from, Position to);

    /*
     * Checks if the current player is in checkmate
     * @param currentPlayerColor - color of the current player
     */
    bool isCheckmate(Color currentPlayerColor);


    /*
     * Get opponent's king position
     * @param currentPlayerColor - color of the current player
     */
    Position getOpponentKingPosition(Color currentPlayerColor);

    /*
     * Checks if the move is legal
     * @param board - current board
     * @param currentPos - position of the current player's piece
     * @param newPos - position of the piece to move
     */
    bool isMoveLegal(const Board& board, Position currentPos, Position newPos);

    /*
     * Get legal moves for the current player's piece
     * @implicit param board - current board
     * @param currentPos - position of the current player's piece
     */
    bool isKingAttacked(Color currentPlayerColor);

private:

    Board& board;

    std::vector<Position> getLegalMoves(const Board& board, Position currentPos);
};


#endif //CHESS_CHECKDETECTOR_H
