//
// Created by Anhelina Modenko on 25.09.2023.
//

#ifndef CHESS_FENPARSER_H
#define CHESS_FENPARSER_H

#include <string>

class FENparser {

public:

    /*
     * CONSTRUCTOR
     */
    FENparser(std::string fenString);

    /*
     * FUNCTIONALITY
     */
    void parseFen(const std::string& FEN);
    std::string boardToFen();

private:
    std::string fenString;

};


#endif //CHESS_FENPARSER_H
