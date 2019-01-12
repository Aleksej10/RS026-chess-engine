#ifndef RS_CHESS_BOARD_H
#define RS_CHESS_BOARD_H
#include <iostream>


class board {
public:
    char pos[8][8];
    char flags[6];
    unsigned fifty;

public:

    explicit board(std::string fen);

    board(const board &b);
    board();

    friend std::ostream &operator<<(std::ostream &os, const board &board1);
};



#endif //RS_CHESS_BOARD_H
