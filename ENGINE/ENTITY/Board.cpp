//
// Created by Anhelina Modenko on 11.09.2023.
//

#include "Board.h"
#include "ENGINE/GRAPHICS/ResourceManager/resourceManager.h"
#include "ENGINE/GRAPHICS/Renderer/SpriteRenderer.h"

SpriteRenderer* Renderer;

Board::Board(unsigned int width, unsigned int height) : keys(){
    this->height = height;
    this->width = width;

    this->widthOfSquare = width / 8.0f;
    this->heightOfSquare = height / 8.0f;


    try {
        board = new char[NB_SQ];
        castleRights = new bool*[NB_COLOR];
        for (int i = 0; i < NB_COLOR; ++i) {
            castleRights[i] = new bool[NB_CASTLE];
        }

    } catch (...) {
        // Exception occurred, clean up allocated memory
        delete[] board;
        delete[] castleRights;
        delete[] pieces;

        // Re-throw the exception to propagate it
        throw;
    }

}

void Board::init() {

    std::string initialFEN = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
    ResourceManager::loadShader("/Users/anhelinamodenko/CLionProjects/CHESS/Addons/Shaders/sprite.vert", "/Users/anhelinamodenko/CLionProjects/CHESS/Addons/Shaders/sprite.frag", nullptr, "sprite");
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(this->width),
                                      static_cast<float>(this->height), 0.0f, -1.0f, 1.0f);

    ResourceManager::getShader("sprite").activate();
    ResourceManager::getShader("sprite").setInt("image", 0);
    ResourceManager::getShader("sprite").setMat4("projection", projection);
    Shader myShader;
    myShader = ResourceManager::getShader("sprite");
    Renderer = new SpriteRenderer(myShader);

    ResourceManager::loadTexture("/Users/anhelinamodenko/CLionProjects/CHESS/Addons/media/board.jpeg", false, "board");
    ResourceManager::loadTexture("/Users/anhelinamodenko/CLionProjects/CHESS/Addons/media/highlight.png", true, "highlight");
    ResourceManager::loadTexture("/Users/anhelinamodenko/CLionProjects/CHESS/Addons/media/white_king.png", true, "white_king");
    ResourceManager::loadTexture("/Users/anhelinamodenko/CLionProjects/CHESS/Addons/media/white_queen.png", true, "white_queen");
    ResourceManager::loadTexture("/Users/anhelinamodenko/CLionProjects/CHESS/Addons/media/white_rook.png", true, "white_rook");
    ResourceManager::loadTexture("/Users/anhelinamodenko/CLionProjects/CHESS/Addons/media/white_bishop.png", true, "white_bishop");
    ResourceManager::loadTexture("/Users/anhelinamodenko/CLionProjects/CHESS/Addons/media/white_knight.png", true, "white_knight");
    ResourceManager::loadTexture("/Users/anhelinamodenko/CLionProjects/CHESS/Addons/media/white_pawn.png", true, "white_pawn");
    ResourceManager::loadTexture("/Users/anhelinamodenko/CLionProjects/CHESS/Addons/media/black_king.png", true, "black_king");
    ResourceManager::loadTexture("/Users/anhelinamodenko/CLionProjects/CHESS/Addons/media/black_queen.png", true, "black_queen");
    ResourceManager::loadTexture("/Users/anhelinamodenko/CLionProjects/CHESS/Addons/media/black_rook.png", true, "black_rook");
    ResourceManager::loadTexture("/Users/anhelinamodenko/CLionProjects/CHESS/Addons/media/black_bishop.png", true, "black_bishop");
    ResourceManager::loadTexture("/Users/anhelinamodenko/CLionProjects/CHESS/Addons/media/black_knight.png", true, "black_knight");
    ResourceManager::loadTexture("/Users/anhelinamodenko/CLionProjects/CHESS/Addons/media/black_pawn.png", true, "black_pawn");

    GameLevel level1;
    level1.load("/Users/anhelinamodenko/CLionProjects/CHESS/Addons/media/tileData.txt", this->width, this->height);
    this->level = level1;
    this->isReversed = false;
    parseFen(initialFEN);


}



void Board::parseFen(const std::string& FEN) {
    fenData = FEN;

    size_t iter = 0;
    int index = 0;

    // Function to set the squares on the board
    auto set_squares = [&](char piece, int count) {
        for (int i = 0; i < count; ++i) {
            if (index < NB_SQ) {
//                board[index] = piece;
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
            {'p', "black_pawn"},
            {'r', "black_rook"},
            {'n', "black_knight"},
            {'b', "black_bishop"},
            {'q', "black_queen"},
            {'k', "black_king"},

            // White pieces
            {'P', "white_pawn"},
            {'R', "white_rook"},
            {'N', "white_knight"},
            {'B', "white_bishop"},
            {'Q', "white_queen"},
            {'K', "white_king"}
    };


    float squareWidth = this->widthOfSquare;
    float squareHeight = this->heightOfSquare;

    int rank = this->isReversed ? 7 : 0; // Start from rank 8 (topmost)
    int file = this->isReversed ? 7 : 0;; // Start from file A (leftmost)

    for (char fenChar : fenData) {
        if (fenChar == '/') {
            this->isReversed ? rank-- : rank++;
            this->isReversed ? file = 7 : file = 0;
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
            this->isReversed ? file-- : file ++;
        }
    }

}

void Board::processInput(float dt) {
    if (Keyboard::keyWentDown(GLFW_KEY_F)) {
        this->isReversed = !this->isReversed;
    }
    doCollisions();
}

Piece* Board::getPieceAt(Position position) const {
    Piece *piece = nullptr;
    if (isValidPosition(position.getRow(), position.getCol())) {
        piece = &pieces[position.getRow() * 8 + position.getCol()];
    }
    return piece;
}

bool Board::isValidPosition(int row, int col) const {
    return row >= 0 && row < 8 && col >= 0 && col < 8;
}

Board::~Board() {
    delete[] board;
    delete[] castleRights;
    delete[] pieces;;
    delete Renderer;
}

void Board::doCollisions() {

    unsigned int x = Mouse::getMouseX();
    unsigned int y = Mouse::getMouseY();

    unsigned int row = y / this->heightOfSquare;
    unsigned int col = x / this->widthOfSquare;

    if (Mouse::buttonWentDown(GLFW_MOUSE_BUTTON_LEFT)) {
        std::cout << "row: " << row+1 << " col: " << col+1 << std::endl;

        Piece* clickedPiece = getPieceAt(Position(row, col));

        if (clickedPiece != nullptr) {
            if (selectedPiece == clickedPiece) {
                // Clicked the same piece again, so unhighlight it
                selectedPiece = nullptr;
            } else {
                selectedPiece = clickedPiece;
            }
        } else {
            // Clear the selected piece if an empty square is clicked
            selectedPiece = nullptr;
        }

    }
}




