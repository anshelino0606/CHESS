//
// Created by Anhelina Modenko on 11.09.2023.
//

#ifndef CHESS_BOARD_H
#define CHESS_BOARD_H

#include <string>
#include "Piece.h"
#include "ENGINE/GRAPHICS/Texture/texture.h"
#include "ENGINE/IO/keyboard.h"
#include "ENGINE/IO/mouse.h"
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
    std::string boardToFen();
    void processInput(float dt);
    void init();
    void update();
    void render();
    void doCollisions();

    void renderHighlight(Position position);
    void removeHighlight(Position position);
    void makeMove(Position from, Position to);

    bool isEmpty(int row, int col) const;
    bool isOpponent(int row, int col, Color currentPlayerColor) const;
    bool isValidPosition(int row, int col) const;

    Piece* getPieceAt(Position position) const;


    ~Board();

private:
    Color turn;
    std::string enPassant;
    std::string fenData;

    char* board;
    bool** castleRights;
    Piece* pieces;
    Piece* selectedPiece;

    unsigned int width, height;
    unsigned int widthOfSquare, heightOfSquare;

    unsigned int rowSelected;
    unsigned int colSelected;

    bool isReversed;
};


#endif //CHESS_BOARD_H
