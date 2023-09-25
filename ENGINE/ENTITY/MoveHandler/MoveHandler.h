//
// Created by Anhelina Modenko on 25.09.2023.
//

#ifndef CHESS_MOVEHANDLER_H
#define CHESS_MOVEHANDLER_H

#include "ENGINE/ENTITY/Board/Board.h"

class Board;
enum class Color;

class MoveHandler {

public:

    /*
     * CONSTRUCTOR
     */
    MoveHandler();

    explicit MoveHandler(Board &board);



    /*
     * FUNCTIONS
     */

    /*
     * Moves a piece from one cell to another
     * @param from - position of the piece to move
     * @param to - position of the cell to move to
     * @explicit param board - board to move on
     */
    bool makeMove(Position from, Position to);

    /*
     * Checks if the cell is empty
     * in a char* array of 64 elements
     * @param row - row of the cell
     * @param col - column of the cell
     */
    bool isEmpty(int row, int col) const;

    /*
     * Checks if the cell has Piece of opposite color
     * @param row - row of the cell
     * @param col - column of the cell
     * @param currentPlayerColor - color of the current player
     */
    bool isOppositeColor(int row, int col, Color currentPlayerColor) const;


    /*
     * Checks if position is valid
     * @param row - row of the cell
     * @param col - column of the cell
     */
    bool isValidPosition(int row, int col) const;


private:
    Board& board;
};


#endif //CHESS_MOVEHANDLER_H
