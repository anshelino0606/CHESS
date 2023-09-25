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
#include "ENGINE/ENTITY/MoveHandler/MoveHandler.h"

constexpr int NB_SQ = 64;       // Number of squares on the chessboard
constexpr int NB_CASTLE = 2;    // Number of castle types
constexpr int NB_COLOR = 2;     // Number of colors in chess (white and black)

class Piece;

enum class Castle
{
    kingSide,
    queenSide
};

enum class Color
{
    white,
    black,
    none
};

class MoveHandler;

class Board {
public:
    Board(unsigned int width, unsigned int height);

    GameLevel level;

    bool keys[1024];


    /*
     * TODO: implement division into classes
     */

    /*
     * FEN PARSER
     */
    void parseFen(const std::string& FEN);
    std::string boardToFen();

    /*
     * GRAPHICS HANDLING FOR BOARD
     * TODO: leave it in board class
     */
    void processInput(float dt);
    void init();
    void update();
    void render();
    void doCollisions();

    void renderHighlight(Position position);

    /*
     * GETTERS AND SETTERS
     */

    void setSelectedRow(int row);
    void setSelectedCol(int col);
    void setSelectedPiece(Piece* piece);

    Piece* getPieceAt(Position position) const;

    /*
     * DESTRUCTOR
     */

    ~Board();

    char* board;
private:
    Color turn;
    std::string enPassant;
    std::string fenData;

    bool** castleRights;
    Piece* pieces;
    Piece* selectedPiece;
    Piece* draggedPiece;

    unsigned int width, height;
    unsigned int widthOfSquare, heightOfSquare;

    int rowSelected;
    int colSelected;

    bool isReversed;
    bool moveMade;
    bool isHighlighted;
    std::vector<Position> legalMoves;

    MoveHandler* moveHandler;

    friend class MoveHandler;
};


#endif //CHESS_BOARD_H
