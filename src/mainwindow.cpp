#include "headers/mainwindow.h"
#include "ui_mainwindow.h"

#include <QApplication>
#include <QDesktopWidget>
#include <QCoreApplication>
#include <QHeaderView>
#include <QMessageBox>
#include "headers/board.h"
#include "headers/move.h"
#include <vector>
#include "QDir"
#include <QPainter>
#include <QGraphicsPixmapItem>
#include <QMediaPlayer>
#include "QPushButton"
#include "QLayout"

#include "QBoxLayout"

#include "QThread"
#include "QStyleFactory"
#include "QVBoxLayout"
#include "QGroupBox"
#include "QtSvg/QSvgWidget"
#include "QStyle"

#define SIZE 700

//globals
static bool color = false; // true for white
static board initial("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
static bool Hl = false;
static std::vector<move1> moves;

std::pair<int, int> MainWindow::translate(int x, int y) {
    //translate coordinates respective to color
    if(color)
        return std::pair<int, int>(x, y);
    return std::pair<int, int>(7-x, 7-y);
}

void MainWindow::resetColors(){
    //colors the squares
    for(int i = 0;i<8;i++) {
        for(int j = 0;j<8;j++) {
            if((i%2 == 0 && j % 2 == 1) || (i % 2 == 1 && j % 2 == 0))
                tw->item(i, j)->setBackgroundColor(QColor(113, 86, 67));
            else if((i %2 == 0 && j %2 == 0) || (i % 2 == 1 && j % 2 == 1))
                tw->item(i, j)->setBackgroundColor(QColor(219, 189, 169));
        }
    }
}

void MainWindow::setHighlight(int x, int y) {
    auto par = MainWindow::translate(x,y);
    tw->item(par.first, par.second)->setBackgroundColor(QColor(255, 215, 40));
}

void MainWindow::lastMove(int x, int y){
    auto par = MainWindow::translate(x,y);
    tw->item(par.first, par.second)->setBackgroundColor(QColor(196, 92, 17));
}


void MainWindow::generateBoard(board &b) {
    for(int x = 0;x<8;x++) {
        for(int y = 0;y<8;y++) {
            char c = b.pos[x][y];

            auto par = MainWindow::translate(x,y);
            int i=par.first;
            int j=par.second;

            if(c == 'r'){
                QString imgPath = ":/images/images/black_rook.png";
                QImage *img = new QImage(imgPath);
                tw->item(i, j)->setData(Qt::DecorationRole, QPixmap::fromImage(*img));
            }
            else if(c == 'R'){
                QString imgPath = ":/images/images/white_rook.png";
                QImage *img = new QImage(imgPath);
                tw->item(i, j)->setData(Qt::DecorationRole, QPixmap::fromImage(*img));
            }
            else if(c == 'n'){
                QString imgPath = ":/images/images/black_knight.png";
                QImage *img = new QImage(imgPath);
                tw->item(i, j)->setData(Qt::DecorationRole, QPixmap::fromImage(*img));
            }
            else if(c == 'N'){
                QString imgPath = ":/images/images/white_knight.png";
                QImage *img = new QImage(imgPath);
                tw->item(i, j)->setData(Qt::DecorationRole, QPixmap::fromImage(*img));
            }
            else if(c == 'b'){
                QString imgPath = ":/images/images/black_bishop.png";
                QImage *img = new QImage(imgPath);
                tw->item(i, j)->setData(Qt::DecorationRole, QPixmap::fromImage(*img));
            }
            else if(c == 'B'){
                QString imgPath = ":/images/images/white_bishop.png";
                QImage *img = new QImage(imgPath);
                tw->item(i, j)->setData(Qt::DecorationRole, QPixmap::fromImage(*img));
            }
            else if(c == 'q'){
                QString imgPath = ":/images/images/black_queen.png";
                QImage *img = new QImage(imgPath);
                tw->item(i, j)->setData(Qt::DecorationRole, QPixmap::fromImage(*img));
            }
            else if(c == 'Q'){
                QString imgPath = ":/images/images/white_queen.png";
                QImage *img = new QImage(imgPath);
                tw->item(i, j)->setData(Qt::DecorationRole, QPixmap::fromImage(*img));
            }
            else if(c == 'k'){
                QString imgPath = ":/images/images/black_king.png";
                QImage *img = new QImage(imgPath);
                tw->item(i, j)->setData(Qt::DecorationRole, QPixmap::fromImage(*img));
            }
            else if(c == 'K'){
                QString imgPath = ":/images/images/white_king.png";
                QImage *img = new QImage(imgPath);
                tw->item(i, j)->setData(Qt::DecorationRole, QPixmap::fromImage(*img));
            }
            else if(c == 'p'){
                QString imgPath = ":/images/images/black_pawn.png";
                QImage *img = new QImage(imgPath);
                tw->item(i, j)->setData(Qt::DecorationRole, QPixmap::fromImage(*img));
            }
            else if(c == 'P'){
                QString imgPath = ":/images/images/white_pawn.png";
                QImage *img = new QImage(imgPath);
                tw->item(i, j)->setData(Qt::DecorationRole, QPixmap::fromImage(*img));
            }
            else if(c == '_'){
                QString imgPath = ":/images/images/transparent.png";
                QImage *img = new QImage(imgPath);
                tw->item(i, j)->setData(Qt::DecorationRole, QPixmap::fromImage(*img));
            }
        }
    }
}

void MainWindow::generateSnd() {
    QMediaPlayer *player = new QMediaPlayer;
    player->setMedia(QUrl("qrc:/sound/sound/arrow.mp3"));
    player->setVolume(50);
    player->play();
}

void MainWindow::handleWhiteButton() {
    color = true;
    initial = board("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
    generateBoard(initial);
    tw->setVisible(true);
    emit sideToMove();
}

void MainWindow::handleBlackButton() {
    color = false;
    initial = board("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
    generateBoard(initial);
    tw->setVisible(true);
    emit sideToMove();
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      tw(nullptr)
{
    this->setWindowTitle("Chess");
    this->setFixedSize(SIZE, SIZE);

    QPushButton *buttonWhite = new QPushButton("WHITE", this);
    QPushButton *buttonBlack = new QPushButton("BLACK", this);
    const QSize BUTTON_SIZE = QSize(150, 25);
    buttonBlack->setMinimumSize(BUTTON_SIZE);
    buttonWhite->setMinimumSize(BUTTON_SIZE);

    QPalette pal = buttonWhite->palette();
    pal.setColor(QPalette::Button, QColor(Qt::black));
    buttonWhite->setAutoFillBackground(true);
    buttonWhite->setPalette(pal);
    buttonWhite->setStyleSheet("color: rgb(255, 255, 255)");
    buttonWhite->update();

    QPalette pal2 = buttonBlack->palette();
    pal2.setColor(QPalette::Button, QColor(Qt::black));
    buttonBlack->setAutoFillBackground(true);
    buttonBlack->setPalette(pal2);
    buttonBlack->setStyleSheet("color: rgb(255, 255, 255)");
    buttonBlack->update();

    buttonWhite->move(SIZE/2-160, SIZE-60);
    buttonBlack->move(SIZE/2+10, SIZE-60);

    connect(buttonWhite, SIGNAL (clicked()),this, SLOT (handleWhiteButton()));
    connect(buttonBlack, SIGNAL (clicked()),this, SLOT (handleBlackButton()));

    tw = new QTableWidget(this);
    tw->setMinimumWidth(SIZE);
    tw->setMinimumHeight(SIZE);
    tw->setRowCount(8);
    tw->setColumnCount(8);
    tw->verticalHeader()->setVisible(false);
    tw->horizontalHeader()->setVisible(false);
    tw->horizontalHeader()->setDefaultSectionSize(SIZE/8);
    tw->verticalHeader()->setDefaultSectionSize(SIZE/8);
    tw->setVisible(false);
    tw->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    tw->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    for(int i = 0;i<8;i++) {
        for(int j = 0;j<8;j++) {
            tw->setItem(i, j, new QTableWidgetItem());
            tw->item(i, j)->setFlags(tw->item(i, j)->flags() ^ Qt::ItemIsEditable);
            if((i%2 == 0 && j % 2 == 1) || (i % 2 == 1 && j % 2 == 0))
                tw->item(i, j)->setBackgroundColor(QColor(113, 86, 67));
            else if((i %2 == 0 && j %2 == 0) || (i % 2 == 1 && j % 2 == 1))
                tw->item(i, j)->setBackgroundColor(QColor(219, 189, 169));
        }
    }

    connect(this, SIGNAL(sideToMove()), this, SLOT(sideMoved()));
    connect(tw, SIGNAL(cellPressed(int, int)), this, SLOT(cellSelected(int, int)));

}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::isOver(){
    if(move1::isDraw(initial) || move1::isMate(initial)){
        QMessageBox finish;
        finish.setText("Game is finished!");
        finish.setWindowTitle("  ");
        finish.exec();
        tw->setVisible(false);
    }
}

void MainWindow::sideMoved(){
    if((color && (initial.flags[0]=='k')) || (!color && (initial.flags[0]=='K'))){
        isOver();
        move1 m = move1::stupidMode(initial,4).first;
        move1::playMove(initial,m);
        generateBoard(initial);
        generateSnd();

        resetColors();
        lastMove(m.x, m.y);
        lastMove(m.x1, m.y1);
        Hl = false;
        isOver();
    }
}

void MainWindow::playSelection(int x, int y){
    isOver();
    int k=0;
    auto par = MainWindow::translate(x,y);
    x = par.first;
    y = par.second;

    for (auto m: moves){
        if ((m.x1 == x) && (m.y1 == y)){
            k=1;
            move1::playMove(initial, m);
            generateSnd();
            generateBoard(initial);
            resetColors();
            QCoreApplication::processEvents();
            break;
        }
    }
    if(k==1){
        emit sideToMove();
    }
    else{
        Hl = false;
        resetColors();
    }
}

void MainWindow::cellSelected(int x, int y) {
    int x1 = x;
    int y1 = y;

    auto par = MainWindow::translate(x,y);
    x = par.first;
    y = par.second;
    if (Hl){
        playSelection(x1,y1);
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
