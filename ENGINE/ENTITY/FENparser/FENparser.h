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
    void parseFen(const std::string& FEN);
    std::string boardToFen();

private:
    std::string fenString;
    Board& board;

};


#endif //CHESS_FENPARSER_H
