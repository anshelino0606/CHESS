//
// Created by Anhelina Modenko on 25.09.2023.
//

#include "FENparser.h"

FENparser::FENparser(std::string fenString, Board &board)
    : fenString(fenString), board(board) {}

void FENparser::parseFen(const std::string& FEN) {
    fenString = FEN;
    board.fenData = FEN;

    size_t iter = 0;
    int index = 0;


    // Function to set the squares on the board
    auto set_squares = [&](char piece, int count) {
        for (int i = 0; i < count; ++i) {
            if (index < NB_SQ) {
                board.board[index] = piece;
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


    ++iter;
    if (iter < FEN.size() && FEN[iter] == 'w') {
        board.turn = Color::white;
    }
    else if (iter < FEN.size() && FEN[iter] == 'b') {
        board.turn = Color::black;
    }

    iter += 2;
    while (iter < FEN.size() && FEN[iter] != ' ') {
        if (FEN[iter] == 'k') {
            board.castleRights[static_cast<int>(Color::black)][static_cast<int>(Castle::kingSide)] = true;
        }
        else if (FEN[iter] == 'K') {
            board.castleRights[static_cast<int>(Color::white)][static_cast<int>(Castle::kingSide)] = true;
        }
        else if (FEN[iter] == 'q') {
            board.castleRights[static_cast<int>(Color::black)][static_cast<int>(Castle::queenSide)] = true;
        }
        else if (FEN[iter] == 'Q') {
            board.castleRights[static_cast<int>(Color::white)][static_cast<int>(Castle::queenSide)] = true;
        }
        ++iter;
    }

    if (iter + 1 < FEN.size() && FEN[iter] == ' ') {
        board.enPassant = FEN.substr(iter + 1, 2);
    }
    else {
        board.enPassant = "";
    }
}

std::string FENparser::boardToFen() {

    std::string fen = "";
    int emptyCount = 0;

    for (int i = 0; i < NB_SQ; i++) {
        if (i % 8 == 0 && i != 0) {
            if (emptyCount > 0) {
                fen += std::to_string(emptyCount);
                emptyCount = 0;
            }
            fen += '/';
        }

        if (board.board[i] == '.') {
            emptyCount++;
        } else {
            if (emptyCount > 0) {
                fen += std::to_string(emptyCount);
                emptyCount = 0;
            }
            fen += board.board[i];
        }
    }
    if (emptyCount > 0) {
        fen += std::to_string(emptyCount);
    }

    fen += " ";
    fen += board.turn == Color::white ? "w" : "b";

    fen += " ";
    if (board.castleRights[0][0] || board.castleRights[0][1] || board.castleRights[1][0] || board.castleRights[1][1]) {
        if (board.castleRights[0][0]) fen += 'K';
        if (board.castleRights[0][1]) fen += 'Q';
        if (board.castleRights[1][0]) fen += 'k';
        if (board.castleRights[1][1]) fen += 'q';
    } else {
        fen += '-';
    }

    fen += " ";
    fen += board.enPassant;

    fen += " ";
    fen += "0";

    fen += " ";
    fen += "1";

    return fen;


}
