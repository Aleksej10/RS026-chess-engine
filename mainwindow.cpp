#include "mainwindow.h"

#include <QApplication>
#include <QDesktopWidget>
#include <QCoreApplication>
#include <QHeaderView>
#include <QMessageBox>
#include "board.h"
#include "move.h"
#include <vector>


board initial("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
//board initial("r1bq1rk1/pp2ppbp/2np1np1/8/2BNP3/2N1BP2/PPPQ2PP/R3K2R w KQ - 4 9");
bool Hl = false;
std::vector<move1> moves;

void MainWindow::resetColors(){
    for(int i = 0;i<8;i++) {
        for(int j = 0;j<8;j++) {
            if((i%2 == 0 && j % 2 == 1) || (i % 2 == 1 && j % 2 == 0))
                tw->item(i, j)->setBackgroundColor(QColor(219, 189, 169));
            else if((i %2 == 0 && j %2 == 0) || (i % 2 == 1 && j % 2 == 1))
                tw->item(i, j)->setBackgroundColor(QColor(113, 86, 67));
        }
    }
}

void MainWindow::setHighlight(int x, int y) {
    //QString imgPath = "/home/aleksej/Desktop/tmp/CHESS/CHESS_PravaVerzija/circle.png";
    //QImage *img = new QImage(imgPath);
    //tw->item(x, y)->setData(Qt::DecorationRole, QPixmap::fromImage(*img));
    tw->item(x, y)->setBackgroundColor(Qt::yellow);
}


void MainWindow::generateBoard(board &b) {
    for(int i = 0;i<8;i++) {
        for(int j = 0;j<8;j++) {
            char c = b.pos[i][j];
            if(c == 'r'){
                QString imgPath = "/home/aleksej/Desktop/svgz/rook.svg";
                QImage *img = new QImage(imgPath);
                tw->item(i, j)->setData(Qt::DecorationRole, QPixmap::fromImage(*img).scaled(80, 80));
            }
            else if(c == 'R'){
                QString imgPath = "/home/aleksej/Desktop/svgz/rook1.svg";
                QImage *img = new QImage(imgPath);
                tw->item(i, j)->setData(Qt::DecorationRole, QPixmap::fromImage(*img).scaled(80, 80));
            }
            else if(c == 'n'){
                QString imgPath = "/home/aleksej/Desktop/svgz/knight.svg";
                QImage *img = new QImage(imgPath);
                tw->item(i, j)->setData(Qt::DecorationRole, QPixmap::fromImage(*img).scaled(80, 80));
            }
            else if(c == 'N'){
                QString imgPath = "/home/aleksej/Desktop/svgz/knight1.svg";
                QImage *img = new QImage(imgPath);
                tw->item(i, j)->setData(Qt::DecorationRole, QPixmap::fromImage(*img).scaled(80, 80));
            }
            else if(c == 'b'){
                QString imgPath = "/home/aleksej/Desktop/svgz/bishop.svg";
                QImage *img = new QImage(imgPath);
                tw->item(i, j)->setData(Qt::DecorationRole, QPixmap::fromImage(*img).scaled(80, 80));
            }
            else if(c == 'B'){
                QString imgPath = "/home/aleksej/Desktop/svgz/bishop1.svg";
                QImage *img = new QImage(imgPath);
                tw->item(i, j)->setData(Qt::DecorationRole, QPixmap::fromImage(*img).scaled(80, 80));
            }
            else if(c == 'q'){
                QString imgPath = "/home/aleksej/Desktop/svgz/queen.svg";
                QImage *img = new QImage(imgPath);
                tw->item(i, j)->setData(Qt::DecorationRole, QPixmap::fromImage(*img).scaled(80, 80));
            }
            else if(c == 'Q'){
                QString imgPath = "/home/aleksej/Desktop/svgz/queen1.svg";
                QImage *img = new QImage(imgPath);
                tw->item(i, j)->setData(Qt::DecorationRole, QPixmap::fromImage(*img).scaled(80, 80));
            }
            else if(c == 'k'){
                QString imgPath = "/home/aleksej/Desktop/svgz/king.svg";
                QImage *img = new QImage(imgPath);
                tw->item(i, j)->setData(Qt::DecorationRole, QPixmap::fromImage(*img).scaled(80, 80));
            }
            else if(c == 'K'){
                QString imgPath = "/home/aleksej/Desktop/svgz/king1.svg";
                QImage *img = new QImage(imgPath);
                tw->item(i, j)->setData(Qt::DecorationRole, QPixmap::fromImage(*img).scaled(80, 80));
            }
            else if(c == 'p'){
                QString imgPath = "/home/aleksej/Desktop/svgz/pawn.svg";
                QImage *img = new QImage(imgPath);
                tw->item(i, j)->setData(Qt::DecorationRole, QPixmap::fromImage(*img).scaled(80, 80));
            }
            else if(c == 'P'){
                QString imgPath = "/home/aleksej/Desktop/svgz/pawn1.svg";
                QImage *img = new QImage(imgPath);
                tw->item(i, j)->setData(Qt::DecorationRole, QPixmap::fromImage(*img).scaled(80, 80));
            }
            else if(c == '_'){
                QString imgPath = "/home/aleksej/Desktop/tmp/CHESS/CHESS_PravaVerzija/transparent.png";
                QImage *img = new QImage(imgPath);
                tw->item(i, j)->setData(Qt::DecorationRole, QPixmap::fromImage(*img).scaled(80, 80));
            }
        }
    }
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      tw(NULL)
{
    this->setWindowTitle("Chess");
    this->setFixedSize(700, 700);


    tw = new QTableWidget(this);
    tw->setMinimumWidth(700);
    tw->setMinimumHeight(700);
    tw->setRowCount(8);
    tw->setColumnCount(8);
    tw->verticalHeader()->setVisible(false);
    tw->horizontalHeader()->setVisible(false);
    tw->horizontalHeader()->setDefaultSectionSize(80);
    tw->verticalHeader()->setDefaultSectionSize(80);
    tw->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    tw->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    for(int i = 0;i<8;i++) {
        for(int j = 0;j<8;j++) {
            tw->setItem(i, j, new QTableWidgetItem());
            tw->item(i, j)->setFlags(tw->item(i, j)->flags() ^ Qt::ItemIsEditable);
            if((i%2 == 0 && j%2 == 1) || (i%2 == 1 && j%2 == 0))
                tw->item(i, j)->setBackgroundColor(QColor(219, 189, 169));
            else
                tw->item(i, j)->setBackgroundColor(QColor(113, 86, 67));
        }
    }




    generateBoard(initial);

    connect(tw, SIGNAL(cellPressed(int, int)), this, SLOT(cellSelected(int, int)));
//    while(!move1::isDraw(initial) && !move1::isMate(initial)){
//        if(initial.flags[0]=='K'){
//        }
//        else{
//                move1 m = move1::stupidMode(initial,3).first;
//                move1::playMove(initial,m);
//        }
//    }

}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::playSelection(int x, int y){
    int k=0;
    for (auto m: moves){
        if ((m.x1 == x) && (m.y1 == y)){
            k=1;
            move1::playMove(initial, m);
            resetColors();
            generateBoard(initial);
            break;
        }
    }
    if(k==1){
            move1 m = move1::stupidMode(initial,3).first;
            move1::playMove(initial,m);
            generateBoard(initial);
    }
    Hl = false;
}

void MainWindow::cellSelected(int x, int y) {
    if (Hl){
        playSelection(x,y);
    }
    else{
        if(initial.pos[x][y] == 'r' || initial.pos[x][y] == 'R') {
            resetColors();
            moves.clear();
            move1::rook(moves, initial, x, y);
            if(moves.empty()){
                Hl = false;
                return;
            }
            for(move1 m : moves) {
                setHighlight(m.x1, m.y1);
            }
            Hl = true;
        }
        else if((initial.pos[x][y] == 'n') || (initial.pos[x][y] == 'N')) {
            resetColors();
            moves.clear();
            move1::knight(moves,initial, x, y);
            if(moves.empty()){
                Hl = false;
                return;
            }
            for(move1 m : moves) {
                setHighlight(m.x1, m.y1);
            }
            Hl = true;
        }
        else  if(initial.pos[x][y] == 'b' || initial.pos[x][y] == 'B') {
            resetColors();
            moves.clear();
            move1::bishop(moves, initial, x, y);
            if(moves.empty()){
                Hl = false;
                return;
            }
            for(move1 m : moves) {
                setHighlight(m.x1, m.y1);
            }
            Hl = true;
        }
        else if(initial.pos[x][y] == 'q' || initial.pos[x][y] == 'Q') {
            resetColors();
            moves.clear();
            move1::queen(moves, initial, x, y);
            if(moves.empty()){
                Hl = false;
                return;
            }
            for(move1 m : moves) {
                setHighlight(m.x1, m.y1);
            }
            Hl = true;
        }
        else if(initial.pos[x][y] == 'k' || initial.pos[x][y] == 'K') {
            resetColors();
            moves.clear();
            move1::king(moves,initial, x, y);
            if(moves.empty()){
                Hl = false;
                return;
            }
            for(move1 m : moves) {
                setHighlight(m.x1, m.y1);
            }
            Hl = true;
        }
        else if(initial.pos[x][y] == 'p' || initial.pos[x][y] == 'P') {
            resetColors();
            moves.clear();
            move1::pawn(moves, initial, x, y);
            if(moves.empty()){
                Hl = false;
                return;
            }
            for(move1 m : moves) {
                setHighlight(m.x1, m.y1);
            }
            Hl = true;
        }
        else{
            resetColors();
            Hl = false;
        }
    }
}
