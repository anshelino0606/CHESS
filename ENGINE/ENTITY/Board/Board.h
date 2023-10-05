//
// Created by Anhelina Modenko on 11.09.2023.
//

#ifndef CHESS_BOARD_H
#define CHESS_BOARD_H

#include <string>
#include "ENGINE/ENTITY/Move/Move.hpp"
#include "ENGINE/ENTITY/Piece/Piece.h"
#include "ENGINE/GRAPHICS/Texture/texture.h"
#include "ENGINE/IO/keyboard.h"
#include "ENGINE/IO/mouse.h"
#include "ENGINE/GRAPHICS/GameLevel/GameLevel.h"
#include "ENGINE/ENTITY/MoveHandler/MoveHandler.h"
#include "ENGINE/ENTITY/FENparser/FENparser.h"
#include "ENGINE/ENTITY/CheckDetector/CheckDetector.h"

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
class FENparser;
class CheckDetector;

class Board {
public:
    /*
     * CONSTRUCTOR
     */
    Board(unsigned int width, unsigned int height);
    // copy constructor
    Board(const Board& other);

    /*
     * GRAPHICS HANDLING FOR BOARD
     */
    void processInput(float dt);
    void init();
    void update();
    void render();
    void doCollisions();

    void renderHighlight(Position position);

    // Function to make a move and update move history
    bool makeMove(Position from, Position to);

    // Function to check for check
    bool isCheck(Color currentPlayerColor);

    // Function to check for checkmate
    bool isCheckmate(Color currentPlayerColor);

    // Function to check for pins
    bool isPin(Color currentPlayerColor, Position from, Position to);

    static Color getColor(char symbol);

    std::vector<Piece*> getOppositePieces(Color color);

    std::vector<Position> filterMovesToEscapeCheck(Color playerColor);
    std::vector<Piece*> getCurrentPlayerPieces(Color currentPlayer);

    /*
     * GETTER OF PIECE
     */

    Piece* getPieceAt(Position position) const;

    /*
     * DESTRUCTOR
     */


    ~Board();


private:
    char* board;

    GameLevel level;
    bool keys[1024];

    Color turn;
    bool** castleRights;
    std::string enPassant;
    std::string fenData;

//    Piece* pieces;
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

    std::vector<Move> tableOfMoves;

    MoveHandler* moveHandler;
    FENparser* fenParser;
    CheckDetector* checkDetector;

    Position findKingPosition(Color playerColor) const;

    friend class MoveHandler;
    friend class FENparser;
    friend class CheckDetector;
};



#endif //CHESS_BOARD_H
