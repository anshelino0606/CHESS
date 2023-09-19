//
// Created by Anhelina Modenko on 11.09.2023.
//

#ifndef CHESS_BOARD_H
#define CHESS_BOARD_H

#include <string>
#include "Piece.h"
#include "./GRAPHICS/texture.h"

constexpr int NB_SQ = 64;       // Number of squares on the chessboard
constexpr int NB_CASTLE = 2;    // Number of castle types
constexpr int NB_COLOR = 2;     // Number of colors in chess (white and black)

enum class Castle
{
    kingSide,
    queenSide
};

enum class Color
{
    white,
    black
};

class Board {
public:
    Board();

    void parseFen(const std::string& FEN);
    void init();
    void update();
    void render();


    ~Board();

private:
    Texture2D lightSquare;
    Texture2D darkSquare;

    Color turn;
    std::string enPassant;

    char* board;
    bool** castleRights;


};


#endif //CHESS_BOARD_H
