//
// Created by Anhelina Modenko on 11.09.2023.
//

#include "Board.h"
#include "./GRAPHICS/resourceManager.h"

void Board::init() {

    ResourceManager::loadTexture("", true, "light");
    ResourceManager::loadTexture("", true, "dark");

    // TODO: load as a game level

    for (int i = 0; i < 32; i++) {
        // TODO: implement pawn initialization
        // PARSE FEN NOTATION
    }
}



Board::Board() {
    board = new char[NB_SQ];
    castleRights = new bool*[NB_COLOR];
    for (int i = 0; i < NB_COLOR; ++i) {
        castleRights[i] = new bool[NB_CASTLE];
    }


}

Board::~Board() {
    delete[] board;
    for (int i = 0; i < NB_COLOR; i++) {
        delete[] castleRights[i];
    }
    delete[] castleRights;
}

void Board::parseFen(const std::string& FEN)
{
    size_t iter = 0;
    int index = 0;

    // Function to set the squares on the board
    auto set_squares = [&](char piece, int count) {
        for (int i = 0; i < count; ++i) {
            if (index < NB_SQ) {
                board[index] = piece;
                ++index;
            }
            else {
                // Handle malformed FEN (buffer overflow)
                // You may want to throw an exception or handle this differently
                break;
            }
        }
    };

    // Parse the board
    while (iter < FEN.size() && FEN[iter] != ' ') {
        if (FEN[iter] == '/') {
            // Handle malformed FEN (no more than 8 files in a rank)
            // You may want to throw an exception or handle this differently
        }
        else if (isdigit(FEN[iter])) {
            int count = FEN[iter] - '0';
            set_squares('.', count);
        }
        else {
            set_squares(FEN[iter], 1);
        }
        ++iter;
    }

    // Parse the turn
    ++iter;
    if (iter < FEN.size() && FEN[iter] == 'w') {
        turn = Color::white;
    }
    else if (iter < FEN.size() && FEN[iter] == 'b') {
        turn = Color::black;
    }

    // Parse the castling rights
    iter += 2;
    while (iter < FEN.size() && FEN[iter] != ' ') {
        if (FEN[iter] == 'k') {
            castleRights[static_cast<int>(Color::black)][static_cast<int>(Castle::kingSide)] = true;
        }
        else if (FEN[iter] == 'K') {
            castleRights[static_cast<int>(Color::white)][static_cast<int>(Castle::kingSide)] = true;
        }
        else if (FEN[iter] == 'q') {
            castleRights[static_cast<int>(Color::black)][static_cast<int>(Castle::queenSide)] = true;
        }
        else if (FEN[iter] == 'Q') {
            castleRights[static_cast<int>(Color::white)][static_cast<int>(Castle::queenSide)] = true;
        }
        ++iter;
    }

    // Parse en passant (if available)
    if (iter + 1 < FEN.size() && FEN[iter] == ' ') {
        enPassant = FEN.substr(iter + 1, 2);
    }
    else {
        enPassant = ""; // No en passant available
    }
}