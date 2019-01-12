#include "headers/move.h"
#include <vector>
#include "headers/board.h"
#include <algorithm>
#include <utility>

int diff(char w, char b){
    if (((w < '_') && (b > '_')) || ((w > '_') && (b < '_'))) {
        return 1;
    }else return 0;
}

int range(int x, int y){
    if (x<0 || x>7) return 0;
    if (y<0 || y>7) return 0;
    return 1;
}

int latteral(char p){
    if(p=='Q' || p=='q' || p=='R' || p=='r')
        return 1;
    else return 0;
}

int diagonal(char p){
    if(p=='Q' || p=='q' || p=='B' || p=='b')
        return 1;
    else return 0;
}



move1::move1(int x, int y, int x1, int y1, char type) : x(x), y(y), x1(x1), y1(y1), type(type) {}


std::ostream &operator<<(std::ostream &os, const move1 &move1) {
    os << (char)('a' + move1.y) << 8 - move1.x << " - "
       << (char)('a' + move1.y1) << 8 - move1.x1 << " " << move1.type << "\n";
    return os;
}

void move1::knight(std::vector<move1> &moves, const board &pos, int x, int y) {
    char side = pos.flags[0];
    if(diff(pos.pos[x][y],side)){
        return;
    }
    int x1,y1;
    for(x1=-2;x1<=2;x1++){
        if(x1==0 || x+x1 < 0 || x+x1 >7) continue;
        for(y1=-2;y1<=2;y1++){
            if(y1==0 || y1==x1 || y1 == -x1 || y+y1 < 0 || y+y1 > 7) continue;
            if((pos.pos[x+x1][y+y1]=='_') || diff(pos.pos[x][y],pos.pos[x+x1][y+y1])){
                move1 m(x,y,x+x1,y+y1,' ');
                safeAdd(moves,pos,m);
            }
        }
    }
}

void move1::bishop(std::vector<move1> &moves, const board &pos, int x, int y){
    char side = pos.flags[0];
    if(diff(pos.pos[x][y],side)){
        return;
    }
    int x1, y1, i;
    for (x1=-1;x1<=1;x1+=2){
        for(y1=-1;y1<=1;y1+=2){
            i = 1;
            while(range(x+x1*i,y+y1*i) && pos.pos[x+x1*i][y+y1*i]=='_'){
                move1 m(x,y, x+x1*i, y+y1*i, ' ');
                safeAdd(moves,pos,m);
                i++;
            }
            if(range(x+x1*i,y+y1*i) && diff(pos.pos[x][y], pos.pos[x+x1*i][y+y1*i])){
                move1 m(x,y, x+x1*i, y+y1*i, ' ');
                safeAdd(moves,pos,m);
            }
        }
    }
}

void move1::rook(std::vector<move1> &moves, const board &pos, int x, int y) {
    char side = pos.flags[0];
    if(diff(pos.pos[x][y],side)){
        return;
    }
    int x1, y1, i;
    for (x1=-1;x1<=1;x1+=1){
        for(y1=-1;y1<=1;y1+=1){
            if((x1==y1) || (x1==-y1)) continue;
            i = 1;
            while(range(x+x1*i,y+y1*i) && pos.pos[x+x1*i][y+y1*i]=='_'){
                move1 m(x,y, x+x1*i, y+y1*i,(char)(y+'0'));
                safeAdd(moves,pos,m);
                i++;
            }
            if(range(x+x1*i,y+y1*i) && diff(pos.pos[x][y], pos.pos[x+x1*i][y+y1*i])){
                move1 m(x,y, x+x1*i, y+y1*i, (char)(y+'0'));
                safeAdd(moves,pos,m);
            }
        }
    }
}

void move1::queen(std::vector<move1> &moves, const board &pos, int x, int y) {
    char side = pos.flags[0];
    if(diff(pos.pos[x][y],side)){
        return;
    }
    int x1, y1, i;
    for (x1=-1;x1<=1;x1++){
        for(y1=-1;y1<=1;y1++){
            if(x1==0 && y1==0) continue;
            i = 1;
            while(range(x+x1*i,y+y1*i) && pos.pos[x+x1*i][y+y1*i]=='_'){
                move1 m(x,y, x+x1*i, y+y1*i, ' ');
                safeAdd(moves,pos,m);
                i++;
            }
            if(range(x+x1*i,y+y1*i) && diff(pos.pos[x][y], pos.pos[x+x1*i][y+y1*i])){
                move1 m(x,y, x+x1*i, y+y1*i, ' ');
                safeAdd(moves,pos,m);
            }
        }
    }
}

void prom(std::vector<move1> &moves, const board &pos, int x, int y, int x1, int y1, char side){
    int sde;
    int dif = 'a' - 'A';
    sde = (side=='K') ? 0 : 1;
    dif = sde*dif;

    move1 m1(x,y,x1, y1, 'Q' + dif);
    move1 m2(x,y,x1, y1, 'N' + dif);
    move1 m3(x,y,x1, y1, 'B' + dif);
    move1 m4(x,y,x1, y1, 'R' + dif);
    move1::safeAdd(moves,pos,m1);
    move1::safeAdd(moves,pos,m2);
    move1::safeAdd(moves,pos,m3);
    move1::safeAdd(moves,pos,m4);
}

void move1::pawn(std::vector<move1> &moves, const board &pos, int x, int y) {
    char side = pos.flags[0];
    if(diff(pos.pos[x][y],side)){
        return;
    }
    if(pos.flags[5]!='-'){
        en_passant(moves,pos,x,y);
    }
    if(side < '_'){// white
        if (x==6){
            if(pos.pos[5][y]=='_' && pos.pos[4][y]=='_'){
                move1 m(x,y,4,y,'e'); //set en passant
                safeAdd(moves,pos,m);
            }
        }
        if(x-1 >= 0){
            if(pos.pos[x-1][y]=='_'){
                if(x==1){
                    prom(moves,pos,x,y,x-1,y,side);
                }
                else{
                    move1 m(x,y,x-1, y, ' ');
                    safeAdd(moves,pos,m);
                }
            }
            if(y-1>= 0 && diff(pos.pos[x][y],pos.pos[x-1][y-1])){
                if(x==1){
                    prom(moves,pos,x,y,x-1,y-1,side);
                }
                else{
                    move1 m(x,y,x-1, y-1,' ');
                    safeAdd(moves,pos,m);
                }
            }
            if(y+1<= 7 && diff(pos.pos[x][y],pos.pos[x-1][y+1])){
                if(x==1){
                    prom(moves,pos,x,y,x-1,y+1,side);
                }
                else{
                    move1 m(x,y,x-1, y+1,' ');
                    safeAdd(moves,pos,m);
                }
            }
        }
    }
    if(side > '_'){
        if (x==1){
            if(pos.pos[2][y]=='_' && pos.pos[3][y]=='_'){
                move1 m(x,y,3,y,'e');
                safeAdd(moves,pos,m);
            }
        }
        if(x+1 <= 7){
            if(pos.pos[x+1][y]=='_'){
                if(x==6){
                    prom(moves,pos,x,y,x+1,y,side);
                }
                else{
                    move1 m(x,y,x+1, y,' ');
                    safeAdd(moves,pos,m);
                }
            }
            if(y-1>= 0 && diff(pos.pos[x][y],pos.pos[x+1][y-1])){
                if(x==6){
                    prom(moves,pos,x,y,x+1,y-1,side);
                }
                else{
                    move1 m(x,y,x+1, y-1,' ');
                    safeAdd(moves,pos,m);
                }
            }
            if(y+1<= 7 && diff(pos.pos[x][y],pos.pos[x+1][y+1])){
                if(x==6){
                    prom(moves,pos,x,y,x+1,y+1,side);
                }
                else{
                    move1 m(x,y,x+1, y+1,' ');
                    safeAdd(moves,pos,m);
                }
            }
        }
    }
}

void move1::en_passant(std::vector<move1> &moves, const board &pos, int x, int y) {
    int e = pos.flags[5] - 'a';
    if(pos.pos[x][y] < '_'){
        if (x != 3) return;
        if(y+1<=7 && e ==y+1){
            move1 m(x,y,x-1,y+1,'E');
            safeAdd(moves,pos,m);
        }
        if(y-1>=0 && e ==y-1){
            move1 m(x,y,x-1,y-1,'E');
            safeAdd(moves,pos,m);
        }
    }
    else{
        if(x != 4) return;
        if(y+1<=7 && e ==y+1){
            move1 m(x,y,x+1,y+1,'E');
            safeAdd(moves,pos,m);
        }
        if(y-1>=0 && e ==y-1){
            move1 m(x,y,x+1,y-1,'E');
            safeAdd(moves,pos,m);
        }
    }
}

void move1::king(std::vector<move1> &moves, const board &pos, int x, int y) {
    char sde = pos.flags[0];
    if(diff(pos.pos[x][y],sde)){
        return;
    }
    castle(moves,pos,x,y);
    int side;
    int dif = 'a' - 'A';
    side = (sde=='K') ? 0 : 1;
    int x1, y1;
    for (x1=-1;x1<=1;x1+=1){
        for(y1=-1;y1<=1;y1+=1){
            if(range(x+x1,y+y1) && ((pos.pos[x+x1][y+y1]=='_') || diff(pos.pos[x][y],pos.pos[x+x1][y+y1]))){
                move1 m(x,y,x+x1,y+y1,static_cast<char>('A' + side*dif));
                safeAdd(moves,pos,m);
            }
        }
    }
}

void move1::castle(std::vector<move1> &moves, const board &pos, int x, int y) {
    char side = pos.flags[0];
    if(side=='K'){//white
        if(pos.flags[1]=='K'){
            if(!attacked(pos,7,4,side) && !attacked(pos,7,5,side) && !attacked(pos,7,6,side)){
                if(pos.pos[7][5]=='_' && pos.pos[7][6]=='_'){
                    moves.emplace_back(move1(x,y,7,6,'K'));
                }
            }
        }
        if(pos.flags[2]=='Q'){
            if(!attacked(pos,7,4,side) && !attacked(pos,7,3,side) && !attacked(pos,7,2,side) && !attacked(pos,7,1,side)){
                if(pos.pos[7][3]=='_' && pos.pos[7][2]=='_' && pos.pos[7][1]=='_'){
                    moves.emplace_back(move1(x,y,7,2,'O'));
                }
            }
        }
    }
    else{
        if(pos.flags[3]=='k'){
            if(!attacked(pos,0,4,side) && !attacked(pos,0,5,side) && !attacked(pos,0,6,side)){
                if(pos.pos[0][5]=='_' && pos.pos[0][6]=='_') {
                    moves.emplace_back(move1(x, y, 0, 6, 'k'));
                }
            }
        }
        if(pos.flags[4]=='q'){
            if(!attacked(pos,0,4,side) && !attacked(pos,0,3,side) && !attacked(pos,0,2,side) && !attacked(pos,0,1,side)){
                if(pos.pos[0][3]=='_' && pos.pos[0][2]=='_' && pos.pos[0][1]=='_') {
                    moves.emplace_back(move1(x, y, 0, 2, 'o'));
                }
            }
        }
    }
}

int move1::attacked(const board &pos, int x, int y, char side) {
    int x1, y1;
    for(x1=-2;x1<=2;x1++){// knight
        if(x1==0 || x+x1 < 0 || x+x1 >7) continue;
        for(y1=-2;y1<=2;y1++){
            if(y1==0 || y1==x1 || y1 == -x1 || y+y1 < 0 || y+y1 > 7) continue;
            if((tolower(pos.pos[x+x1][y+y1])=='n') && diff(side,pos.pos[x+x1][y+y1])){
                return 1;
            }
        }
    }
    int  i;
    for (x1=-1;x1<=1;x1+=1){// rook queen king
        for(y1=-1;y1<=1;y1+=1){
            if((x1==y1) || (x1==-y1)) continue;
            i = 1;
            while(range(x+x1*i,y+y1*i) && pos.pos[x+x1*i][y+y1*i]=='_'){
                i++;
            }
            if(range(x+x1*i,y+y1*i) && i==1){
                if((tolower(pos.pos[x+x1*i][y+y1*i])=='k') && diff(pos.pos[x+x1*i][y+y1*i],side)){
                    return 1;
                }
            }
            if(range(x+x1*i,y+y1*i) && diff(side, pos.pos[x+x1*i][y+y1*i]) && latteral(pos.pos[x+x1*i][y+y1*i])){
                return 1;
            }
        }
    }
    for (x1=-1;x1<=1;x1+=2){ //bishop queen king
        for(y1=-1;y1<=1;y1+=2){
            i = 1;
            while(range(x+x1*i,y+y1*i) && pos.pos[x+x1*i][y+y1*i]=='_'){
                i++;
            }
            if(range(x+x1*i,y+y1*i) && i==1){
                if((tolower(pos.pos[x+x1*i][y+y1*i])=='k') && diff(pos.pos[x+x1*i][y+y1*i],side)){
                    return 1;
                }
            }
            if(range(x+x1*i,y+y1*i) && diff(side, pos.pos[x+x1*i][y+y1*i]) && diagonal(pos.pos[x+x1*i][y+y1*i])){
                return 1;
            }
        }
    }
    if(side=='K'){ //pawn
        if(x-1>=0){
            if(y-1>=0){
                if(pos.pos[x-1][y-1]=='p')
                    return 1;
            }
            if(y+1<=7){
                if(pos.pos[x-1][y+1]=='p')
                    return 1;
            }
        }
    }else{
        if(x+1<=7){
            if(y-1>=0){
                if(pos.pos[x+1][y-1]=='P')
                    return 1;
            }
            if(y+1<=7){
                if(pos.pos[x+1][y+1]=='P')
                    return 1;
            }
        }
    }
    return 0;
}


void move1::playMove(board &pos, const move1 &mov) {
    int side;
    int dif = 'a' - 'A';
    if(pos.flags[0]=='K'){
        side = 0;
        pos.flags[0]='k';
    }else{
        side = 1;
        pos.flags[0]='K';
    }
    dif*=side;

    if(mov.type=='e'){
        pos.flags[5]='a' + mov.y;
        pos.pos[mov.x][mov.y]='_';
        pos.pos[mov.x1][mov.y1]='P'+dif;
        pos.fifty = 0;
    }
    else if(mov.type=='E'){
        pos.flags[5]='-';
        pos.pos[mov.x][mov.y]='_';
        pos.pos[mov.x1][mov.y1]='P'+dif;
        pos.pos[3+side][mov.y1]='_';
        pos.fifty = 0;
    }
    else if(mov.type-'0'==0){
        pos.flags[5]='-';
        pos.flags[2+side*2]=' ';
        pos.pos[mov.x][mov.y]='_';
        pos.pos[mov.x1][mov.y1]=='_' ? (pos.fifty++) : (pos.fifty=0);
        pos.pos[mov.x1][mov.y1]='R'+dif;
    }
    else if(mov.type-'0'==7){
        pos.flags[5]='-';
        pos.flags[1+side*2]=' ';
        pos.pos[mov.x][mov.y]='_';
        pos.pos[mov.x1][mov.y1]=='_' ? (pos.fifty++) : (pos.fifty=0);
        pos.pos[mov.x1][mov.y1]='R'+dif;
    }
    else if(mov.type=='a' || mov.type=='A'){
        pos.flags[5]='-';
        pos.flags[1+side*2]=' ';
        pos.flags[2+side*2]=' ';
        pos.pos[mov.x][mov.y]='_';
        pos.pos[mov.x1][mov.y1]=='_' ? (pos.fifty++) : (pos.fifty=0);
        pos.pos[mov.x1][mov.y1]='K'+dif;
    }
    else if(mov.type=='K' || mov.type=='k'){
        pos.flags[5]='-';
        pos.flags[1+side*2]=' ';
        pos.flags[2+side*2]=' ';
        pos.pos[7-side*7][4]='_';
        pos.pos[7-side*7][7]='_';
        pos.pos[7-side*7][6]='K'+dif;
        pos.pos[7-side*7][5]='R'+dif;
        pos.fifty++;
    }
    else if(mov.type=='O' || mov.type=='o'){
        pos.flags[5]='-';
        pos.flags[1+side*2]=' ';
        pos.flags[2+side*2]=' ';
        pos.pos[7-side*7][4]='_';
        pos.pos[7-side*7][0]='_';
        pos.pos[7-side*7][1]='_';
        pos.pos[7-side*7][2]='K'+dif;
        pos.pos[7-side*7][3]='R'+dif;
        pos.fifty++;
    }
    else if(mov.type=='Q' || mov.type=='q' || mov.type=='N' || mov.type=='n' || mov.type=='B' || mov.type=='b' || mov.type=='R' || mov.type=='r'){
        pos.flags[5]='-';
        pos.pos[mov.x][mov.y]='_';
        pos.pos[mov.x1][mov.y1]=mov.type;
        pos.fifty = 0;
    }
    else{
        pos.flags[5]='-';
        pos.pos[mov.x1][mov.y1]=='_' ? (pos.fifty++) : (pos.fifty=0);
        pos.pos[mov.x1][mov.y1]=pos.pos[mov.x][mov.y];
        pos.pos[mov.x][mov.y]='_';
    }
}

void move1::safeAdd(std::vector<move1> &moves, const board &pos, move1 m) {
    board tmp(pos);
    playMove(tmp,m);
    for(int x=0; x<8; x++){
        for(int y=0; y<8; y++){
            if(tmp.pos[x][y]==pos.flags[0]){
                if(!attacked(tmp,x,y,pos.flags[0])){
                    moves.emplace_back(m);
                }
            }
        }
    }

}

  std::vector<move1> move1::getMoves(const board &pos) {
    std::vector<move1> moves;
    for(int x=0;x<8;x++){
        for(int y=0;y<8;y++){
            switch (tolower(pos.pos[x][y])){
                case 'p': {move1::pawn(moves,pos,x,y); break;}
                case 'n': {move1::knight(moves,pos,x,y); break;}
                case 'b': {move1::bishop(moves,pos,x,y); break;}
                case 'r': {move1::rook(moves,pos,x,y); break;}
                case 'q': {move1::queen(moves,pos,x,y); break;}
                case 'k': {move1::king(moves,pos,x,y); break;}
                default: break;
            }
        }
    }
    return moves;
}

int move1::isMate(const board &pos) {
    for(int x=0;x<8;x++){
        for(int y=0;y<8;y++){
            if(pos.pos[x][y]==pos.flags[0]){
                if(attacked(pos,x,y,pos.flags[0])){
                    std::vector<move1> moves = getMoves(pos);
                    if(moves.empty()){
                        return 1;
                    }
                    else{
                        return 0;
                    }
                }
                else{
                    return 0;
                }
            }
        }
    }
    return 666;
}

int move1::isDraw(const board &pos) {
    if(pos.fifty == 50){
        return 1;
    }
    for(int x=0;x<8;x++){
        for(int y=0;y<8;y++){
            if(pos.pos[x][y]==pos.flags[0]){
                if(!attacked(pos,x,y,pos.flags[0])){
                    std::vector<move1> moves = getMoves(pos);
                    if(moves.empty()){
                        return 1;
                    }
                    else{
                        return 0;
                    }
                }
                else{
                    return 0;
                }
            }
        }
    }
    return 666;
}

int cof(char c){
    if(c < '_') return 1;
    else return -1;
}

int move1::stupidEval(const board &pos) {
    if(isMate(pos)){
        return cof(pos.flags[0]) * (-1000);
    }
    if(isDraw(pos)){
        return 0;
    }
    int sum = 0;
    for(int x=0;x<8;x++){
        for(int y=0;y<8;y++){
            char a = pos.pos[x][y];
            switch (tolower(a)){
                case 'p': {sum+= cof(a); break;}
                case 'n': {sum+= cof(a)*3; break;}
                case 'b': {sum+= cof(a)*3; break;}
                case 'r': {sum+= cof(a)*5; break;}
                case 'q': {sum+= cof(a)*9; break;}
                default: break;
            }
        }
    }
    return sum;
}

std::pair<move1, int> move1::stupidMode(const board &pos, int depth) {
    if (depth == 0){
        return std::pair<move1,int>(move1(0,0,0,0,'W'),stupidEval(pos));
    }
    else{
        std::vector<move1> moves = getMoves(pos);
        if(moves.empty()){
            return std::pair<move1,int>(move1(0,0,0,0,'W'),stupidEval(pos));
        }
        std::vector<int> evals;
        for(move1 m: moves){
            board tmp(pos);
            playMove(tmp,m);
            if(pos.flags[0]=='K'){
                int e = stupidEval(pos);
                if(e < -12){
                    evals.push_back(e);
                    continue;
                }
            }
            else{
                int e = stupidEval(pos);
                if(e > 12){
                    evals.push_back(e);
                    continue;
                }
            }

            std::pair<move1, int> par = stupidMode(tmp, depth - 1);
            if(pos.flags[0]=='K'){
                if(par.second > 12){
                    return std::pair<move1,int>(m,par.second);
                }
            }
            else{
                if(par.second < -12){
                    return std::pair<move1,int>(m,par.second);
                }
            }
            evals.push_back(par.second);
        }
        if(pos.flags[0]=='K'){ //max
            int i = std::max_element(evals.begin(),evals.end()) - evals.begin() ;
            return std::pair<move1,int> (moves[i],evals[i]);
        }
        else{
            int i = std::min_element(evals.begin(),evals.end()) - evals.begin() ;
            return std::pair<move1,int> (moves[i],evals[i]);
        }
    }
}
