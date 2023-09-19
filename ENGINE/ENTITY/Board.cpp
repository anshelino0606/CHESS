//
// Created by Anhelina Modenko on 11.09.2023.
//

#include "Board.h"
#include "ENGINE/GRAPHICS/ResourceManager/resourceManager.h"
#include "ENGINE/GRAPHICS/Renderer/SpriteRenderer.h"

SpriteRenderer* Renderer;

void Board::init() {

    ResourceManager::loadShader("/Users/anhelinamodenko/Documents/Share/MALL_1/Algorithms/Shaders/sprite.vert", "/Users/anhelinamodenko/Documents/Share/MALL_1/Algorithms/Shaders/sprite.frag", nullptr, "sprite");
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(this->width),
                                      static_cast<float>(this->height), 0.0f, -1.0f, 1.0f);

    ResourceManager::getShader("sprite").activate();
    ResourceManager::getShader("sprite").setInt("image", 0);
    ResourceManager::getShader("sprite").setMat4("projection", projection);
    Shader myShader;
    myShader = ResourceManager::getShader("sprite");
    Renderer = new SpriteRenderer(myShader);

    ResourceManager::loadTexture("/Users/anhelinamodenko/CLionProjects/SmartShoppingCart/Game/Assets/Tiles/cursor.png", true, "cursor");



}



Board::Board(unsigned int width, unsigned int height) {
    this->height = height;
    this->width = width;

    this->widthOfSquare = width / 8;
    this->heightOfSquare = height / 8;

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

void Board::parseFen(const std::string& FEN) {
    fenData = FEN;

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


    ++iter;
    if (iter < FEN.size() && FEN[iter] == 'w') {
        turn = Color::white;
    }
    else if (iter < FEN.size() && FEN[iter] == 'b') {
        turn = Color::black;
    }

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

    if (iter + 1 < FEN.size() && FEN[iter] == ' ') {
        enPassant = FEN.substr(iter + 1, 2);
    }
    else {
        enPassant = "";
    }
}

void Board::render() {

    Renderer->DrawSprite(ResourceManager::getTexture("board"),
                         glm::vec2(0.0f, 0.0f),
                         glm::vec2(this->width, this->height),
                         0.0f);

    this->level.draw(*Renderer);

    std::unordered_map<char, std::string> pieceTextureMap = {
            // Black pieces
            {'p', "black_pawn_texture"},
            {'r', "black_rook_texture"},
            {'n', "black_knight_texture"},
            {'b', "black_bishop_texture"},
            {'q', "black_queen_texture"},
            {'k', "black_king_texture"},

            // White pieces
            {'P', "white_pawn_texture"},
            {'R', "white_rook_texture"},
            {'N', "white_knight_texture"},
            {'B', "white_bishop_texture"},
            {'Q', "white_queen_texture"},
            {'K', "white_king_texture"}
    };


    float squareWidth = this->widthOfSquare;
    float squareHeight = this->heightOfSquare;

    int rank = 7; // Start from rank 8 (top of the board)
    int file = 0; // Start from file A (leftmost)

    for (char fenChar : fenData) {
        if (fenChar == '/') {
            rank--;
            file = 0;
        } else if (isdigit(fenChar)) {
            file += fenChar - '0';
        } else if (fenChar == ' ') {
            continue;
        } else {
            auto it = pieceTextureMap.find(fenChar);
            if (it != pieceTextureMap.end()) {
                glm::vec2 piecePosition = glm::vec2(file * squareWidth, rank * squareHeight);

                Renderer->DrawSprite(ResourceManager::getTexture(it->second),
                                     piecePosition,
                                     glm::vec2(squareWidth, squareHeight),
                                     0.0f);
            }
            file++;
        }
    }

}
