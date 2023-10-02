#ifndef MOVE_H
#define MOVE_H

#include "ENGINE/ENTITY/Position/Position.hpp"

class Move {

public:
    Position from;
    Position to;
    char capturedPiece;
};


#endif