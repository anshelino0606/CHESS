
#ifndef POSITION_H
#define POSITION_H


class Position {
public:

    Position() {}

    Position(int row, int col) : row(row), col(col) {}

    int getRow() { return row; }
    int getCol() { return col; }

    bool operator==(const Position& other) const {
        return row == other.row && col == other.col;
    }

    bool operator!=(const Position& other) const {
        return !(*this == other);
    }

private:
    int row;
    int col;

};


#endif