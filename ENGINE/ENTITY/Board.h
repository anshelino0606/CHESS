//
// Created by Anhelina Modenko on 11.09.2023.
//

#ifndef CHESS_BOARD_H
#define CHESS_BOARD_H

#include <string>
#include "Piece.h"
#include "ENGINE/GRAPHICS/Texture/texture.h"
#include "ENGINE/GRAPHICS/GameLevel/GameLevel.h"

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
    Board(unsigned int width, unsigned int height);

    GameLevel level;

    bool keys[1024];

    void parseFen(const std::string& FEN);
    void processInput(float dt);
    void init();
    void update();
    void render();
    void doCollisions();


    ~Board();

private:
    Texture2D lightSquare;
    Texture2D darkSquare;

    Color turn;
    std::string enPassant;
    std::string fenData;

    char* board;
    bool** castleRights;
    Piece pieces[32];

    unsigned int width, height;
    unsigned int widthOfSquare, heightOfSquare;

};


#endif //CHESS_BOARD_H
