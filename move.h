#ifndef RS_CHESS_MOVE_H
#define RS_CHESS_MOVE_H


#include <ostream>
#include <vector>
#include "board.h"
#include <utility>

class move1 {
public:
    int x,y,x1,y1;
    char type;

public:
    move1(int x, int y, int x1, int y1, char type);

    friend std::ostream &operator<<(std::ostream &os, const move1 &move1);

    static void knight(std::vector<move1> &moves, const board &pos, int x, int y);
    static void bishop(std::vector<move1> &moves, const board &pos, int x, int y);
    static void rook(std::vector<move1> &moves, const board &pos, int x, int y);
    static void queen(std::vector<move1> &moves, const board &pos, int x, int y);
    static void pawn(std::vector<move1> &moves, const board &pos, int x, int y);
    static void en_passant(std::vector<move1> &moves, const board &pos, int x, int y);
    static void king(std::vector<move1> &moves, const board &pos, int x, int y);
    static void castle(std::vector<move1> &moves, const board &pos, int x, int y);
    static int attacked(const board &pos, int x, int y, char side);
    static void safeAdd(std::vector<move1> &moves, const board &pos, move1 m);
    static std::vector<move1> getMoves(const board &pos);

    static void playMove(board &pos, const move1 &mov);

    //eval and stuff
    static int isMate(const board &pos);
    static int isDraw(const board &pos);
    static int stupidEval(const board &pos);

    static std::pair<move1,int> stupidMode(const board &pos, int depth);

};


#endif //RS_CHESS_MOVE_H
