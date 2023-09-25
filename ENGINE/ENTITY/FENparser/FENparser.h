//
// Created by Anhelina Modenko on 25.09.2023.
//

#ifndef CHESS_FENPARSER_H
#define CHESS_FENPARSER_H

#include <string>
#include "../Board.h"



class FENparser {

public:

    /*
     * CONSTRUCTOR
     */
    FENparser(std::string fenString, Board& board);

    /*
     * FUNCTIONALITY
     */

    /*
     * Parses the FEN string and sets the board accordingly
     * @param FEN - the FEN string to parse
     * @implicit board - the board to set
     */
    void parseFen(const std::string& FEN);

    /*
     * Converts the board to a FEN string
     * @return the FEN string
     */
    std::string boardToFen();

private:
    std::string fenString;
    Board& board;

};


#endif //CHESS_FENPARSER_H
