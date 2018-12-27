#include "board.h"

board::board(std::string fen){
    int n= fen.size();
    int k=0, i=0;
    while(fen[i]!=' '){
        if (isalpha(fen[i]) != 0) {
            pos[k/8][k%8] = fen[i];
            k++;
        }
        if(isdigit(fen[i])){
            for(int c=0;c<fen[i]-'0';c++){
                pos[k/8][k%8]='_';
                k++;
            }
        }
        i++;
    }
    i++;
    flags[0]= fen[i] == 'w' ? 'K' : 'k';
    i+=2;
    if(fen[i]=='-'){
        for(int s = 1; s<5;s++){
            flags[s]=' ';
        }
        i+=2;
    }else{
        //TODO
        int s = 1;
        while(fen[i]!=' '){
            flags[s] = fen[i];
            i++;
            s++;
        }
        i++;
    }
    flags[5]=fen[i];
    i+=2;
    fen.erase(0,i);
    fifty = stoi(fen);
}

board::board() : board(std::string("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1")){}

board::board(const board &b){
    for(int x=0;x<8;x++){
        for(int y=0;y<8;y++){
            this->pos[x][y] = b.pos[x][y];
        }
    }
    for(int i=0;i<6;i++){
        this->flags[i]=b.flags[i];
    }
    this->fifty = b.fifty;
}

std::ostream &operator<<(std::ostream &os, const board &board1) {
    for(int x=0;x<8;x++){
        for(int y=0;y<8;y++){
            os << board1.pos[x][y] << " ";
        }
        os << "\n";
    }
    os << board1.flags << " " << board1.fifty << "\n";
    return os;
}
