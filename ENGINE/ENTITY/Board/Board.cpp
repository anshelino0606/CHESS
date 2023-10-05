//
// Created by Anhelina Modenko on 11.09.2023.
//

#include "Board.h"
#include "ENGINE/GRAPHICS/ResourceManager/resourceManager.h"
#include "ENGINE/GRAPHICS/Renderer/SpriteRenderer.h"

SpriteRenderer* Renderer;

Board::Board(unsigned int width, unsigned int height) : keys(){

    moveHandler = new MoveHandler(*this);
    fenParser = new FENparser(fenData, *this);
    checkDetector = new CheckDetector(*this);

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

        // pieces array initialize 64 memory blocks



    } catch (...) {
        // Exception occurred, clean up allocated memory
        delete[] board;
        delete[] castleRights;

        // Re-throw the exception to propagate it
        throw;
    }

    moveMade = false;
    isHighlighted = false;



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
    fenParser->parseFen(initialFEN);
    rowSelected = -1;
    colSelected = -1;

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


    renderHighlight(Position(rowSelected, colSelected));
    if (legalMoves.size() != 0 && rowSelected != -1 && colSelected != -1) {
        for (int i = 0; i < legalMoves.size(); ++i) {
            renderHighlight(legalMoves[i]);
        }
    }

}

void Board::processInput(float dt) {
    if (Keyboard::keyWentDown(GLFW_KEY_F)) {
//        this->isReversed = !this->isReversed;
        // print out the board
//        std::cout << "Board: " << std::endl;
//        for (int i = 0; i < NB_SQ; ++i) {
//            std::cout << board[i];
//            if ((i + 1) % 8 == 0) {
//                std::cout << std::endl;
//            }
//        }
    }


    doCollisions();
}

Piece* Board::getPieceAt(Position position) const {
    Piece *piece = nullptr;

    // Check if the position is valid
    if (moveHandler->isValidPosition(position.getRow(), position.getCol())) {
        // Calculate the index of the Piece in the pieces array
        unsigned int index = position.getRow() * 8 + position.getCol();
        int row = position.getRow();
        int col = position.getCol();
        char symbol = board[row * 8 + col];
        Color color = symbol >= 'a' && symbol <= 'z' ? Color::black : Color::white;

        piece = new Piece(symbol, color, position, Piece::pieceTypeMap[symbol], this->moveHandler);

    }

    // Return the piece pointer
    return piece;
}

    void Board::doCollisions() {

    if (Mouse::buttonWentDown(GLFW_MOUSE_BUTTON_LEFT)) {

        unsigned int x = Mouse::getMouseX();
        unsigned int y = Mouse::getMouseY();

        unsigned int row = y / this->heightOfSquare;
        unsigned int col = x / this->widthOfSquare;

        Piece *clickedPiece = getPieceAt(Position(row, col));
        if (selectedPiece == nullptr) {
            // Select a piece
            if (clickedPiece != nullptr && clickedPiece->getSymbol() != '.') {
                if (clickedPiece->getColor() == turn) {
                    selectedPiece = clickedPiece;
                    rowSelected = row;
                    colSelected = col;
                    draggedPiece = clickedPiece;

                    std::cout << "Selected piece: " << selectedPiece->getSymbol() << " " << std::endl;
                    legalMoves = selectedPiece->getLegalMoves(*this, selectedPiece->getPosition());
                    for (int i = 0; i < legalMoves.size(); ++i) {
//                        std::cout << legalMoves[i].getRow() << " " << legalMoves[i].getCol() << std::endl;
                        renderHighlight(legalMoves[i]);
                    }
                } else {
                    std::cout << "Not your turn to move!" << std::endl;
                }
            }
        } else {
            if (selectedPiece != nullptr) {
                // Make a move
                Position target(row, col);

                // if pieces are same color and it's not '.' then we can't move
                if (clickedPiece != nullptr && clickedPiece->getColor() == selectedPiece->getColor() &&
                    clickedPiece->getSymbol() != '.') {
                    std::cout << "Can't move there!" << std::endl;
                    selectedPiece = nullptr;
                    rowSelected = -1;
                    colSelected = -1;
                    return;
                }

                std::unique_ptr<Board> tempBoard = std::make_unique<Board>(*this);

                // Apply the move on the temporary board
                tempBoard->makeMove(selectedPiece->getPosition(), target);
                // update new legal moves
                tempBoard->legalMoves = selectedPiece->getLegalMoves(*tempBoard, target);

                // Check if the move results in the king being in check
                if (tempBoard->isCheck(turn)) {
                    std::cout << "Illegal move! King would be in check." << std::endl;
                    selectedPiece = nullptr;
                    rowSelected = -1;
                    colSelected = -1;
                    return;
                }

                // Check if the target square is a legal move
                if (std::find(legalMoves.begin(), legalMoves.end(), target) == legalMoves.end()) {
                    std::cout << "Illegal move!" << std::endl;
                    selectedPiece = nullptr;
                    rowSelected = -1;
                    colSelected = -1;
                    return;
                }

                // Check that the target square is empty or contains a piece of a different color
                makeMove(selectedPiece->getPosition(), target);
                fenData = fenParser->boardToFen();
                moveMade = true; // Set the flag to true

                // Reset selection
                if (isCheck(turn)) {
                    std::cout << "Check!" << std::endl;
                }
                selectedPiece = nullptr;
                rowSelected = -1;
                colSelected = -1;


                turn = turn == Color::white ? Color::black : Color::white;

                std::cout << "Move made!" << std::endl;
            }
        }

    }

}


void Board::renderHighlight(Position position) {
    // Highlight the square on position
    glm::vec2 highlightPosition = glm::vec2(position.getCol() * widthOfSquare, position.getRow()*heightOfSquare);
    Renderer->DrawSprite(ResourceManager::getTexture("highlight"),
                         highlightPosition,
                         glm::vec2(widthOfSquare, heightOfSquare),
                         0.0f);
}

Board::~Board() {
    delete[] board;
    delete[] castleRights;
//    delete[] pieces;;
//    delete Renderer;
}

Board::Board(const Board &other) {
    this->width = other.width;
    this->height = other.height;
    this->widthOfSquare = other.widthOfSquare;
    this->heightOfSquare = other.heightOfSquare;
    this->level = other.level;
    this->isReversed = other.isReversed;
    this->fenData = other.fenData;
    this->turn = other.turn;
    this->moveMade = other.moveMade;
    this->isHighlighted = other.isHighlighted;
    this->rowSelected = other.rowSelected;
    this->colSelected = other.colSelected;
    this->legalMoves = other.legalMoves;
    this->moveHandler = other.moveHandler;
    this->fenParser = other.fenParser;
    this->checkDetector = other.checkDetector;
    this->board = new char[NB_SQ];
    this->castleRights = new bool*[NB_COLOR];
    for (int i = 0; i < NB_COLOR; ++i) {
        this->castleRights[i] = new bool[NB_CASTLE];
    }
    for (int i = 0; i < NB_SQ; ++i) {
        this->board[i] = other.board[i];
    }
    for (int i = 0; i < NB_COLOR; ++i) {
        for (int j = 0; j < NB_CASTLE; ++j) {
            this->castleRights[i][j] = other.castleRights[i][j];
        }
    }
//    for (int i = 0; i < NB_SQ; ++i) {
//        this->pieces[i] = other.pieces[i];
//    }
    this->selectedPiece = other.selectedPiece;
    this->draggedPiece = other.draggedPiece;
}

Position Board::findKingPosition(Color playerColor) const {
    char kingSymbol = (playerColor == Color::white) ? 'K' : 'k';

    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            if (board[row * 8 + col] == kingSymbol) {
                return Position(row, col);
            }
        }
    }

    return Position(-1, -1);
}

bool Board::isCheck(Color currentPlayerColor) {
    Color opponentColor = currentPlayerColor == Color::white ? Color::black : Color::white;
    Position kingPosition = findKingPosition(currentPlayerColor);

    std::vector<Piece*> opponentPieces = getOppositePieces(currentPlayerColor);

    // Check if any of the opponent's pieces can attack the king
    for (Piece* opponentPiece : opponentPieces) {
        std::vector<Position> legalMoves = opponentPiece->getLegalMoves(*this, opponentPiece->getPosition());
        if (std::find(legalMoves.begin(), legalMoves.end(), kingPosition) != legalMoves.end()) {
            return true;
        }
    }
    return false;
}

Color Board::getColor(char symbol) {
    if (symbol >= 'a' && symbol <= 'z') {
        return Color::black;
    } else if (symbol == '.') {
        return Color::none;
    } else {
        return Color::white;
    }
}

std::vector<Piece *> Board::getOppositePieces(Color color) {
    // get all pieces of the opposite color
    std::vector<Piece*> oppositePieces;
    for (int i = 0; i < NB_SQ; ++i) {
        char piece = board[i];
        if (piece != '.' && getColor(piece) != color) {
            oppositePieces.push_back(getPieceAt(Position(i / 8, i % 8)));

        }
    }
    return oppositePieces;
}

bool Board::makeMove(Position from, Position to) {
    if (!moveHandler->isValidPosition(from.getRow(), from.getCol()) || !moveHandler->isValidPosition(to.getRow(), to.getCol())) {
        return false;
    }

    Piece* piece = getPieceAt(from);
    if (piece == nullptr)
        return false;

    Piece* capturedPiece = getPieceAt(to);
    if (capturedPiece != nullptr) {
        capturedPiece->setPosition(Position(-1, -1));
    }

    piece->setPosition(to);
    board[to.getRow() * 8 + to.getCol()] = board[from.getRow() * 8 + from.getCol()];
    board[from.getRow() * 8 + from.getCol()] = '.';

    selectedPiece = nullptr;
    rowSelected = -1;
    colSelected = -1;

    return false;
}

std::vector<Position> Board::filterMovesToEscapeCheck(Color playerColor) {
    std::vector<Position> filteredMoves;
    Position kingPos = findKingPosition(playerColor);

    // Get all legal moves for the pieces of the current player
    std::vector<Piece*> currentPlayerPieces = getCurrentPlayerPieces(playerColor);

    for (Piece* piece : currentPlayerPieces) {
        std::vector<Position> legalMoves = piece->getLegalMoves(*this, piece->getPosition());

        for (const Position& move : legalMoves) {
            // Create a temporary board to simulate the move
            std::unique_ptr<Board> tempBoard = std::make_unique<Board>(*this);
            tempBoard->makeMove(piece->getPosition(), move);

            // Check if the move removes the king from check
            if (!tempBoard->isCheck(playerColor)) {
                filteredMoves.push_back(move);
            }
        }
    }

    return filteredMoves;
}


std::vector<Piece*> Board::getCurrentPlayerPieces(Color currentPlayer) {
    // get all pieces of currentPlayer color

    std::vector<Piece*> currentPlayerPieces;
    for (int i = 0; i < NB_SQ; ++i) {
        char piece = board[i];
        if (piece != '.' && getColor(piece) == currentPlayer) {
            currentPlayerPieces.push_back(getPieceAt(Position(i / 8, i % 8)));
        }
    }
    return currentPlayerPieces;
}