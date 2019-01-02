#include "mainwindow.h"

#include <QApplication>
#include <QDesktopWidget>
#include <QCoreApplication>
#include <QHeaderView>
#include <QMessageBox>
#include "board.h"
#include "move.h"
#include <vector>
#include "rook.h"
#include "knight.h"
#include "bishop.h"
#include "queen.h"
#include "king.h"
#include "pawn.h"

//board initial("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
board initial("r1bq1rk1/pp2ppbp/2np1np1/8/2BNP3/2N1BP2/PPPQ2PP/R3K2R b KQ - 4 9");

void MainWindow::generateBoard(QTableWidget *tw, board &b) {
    for(int i = 0;i<8;i++) {
        for(int j = 0;j<8;j++) {
            char c = b.pos[i][j];
            if(c == 'r'){
                QString imgPath = "/home/abc/Desktop/RS/CHESS/images/rook.png";
                QImage *img = new QImage(imgPath);
                tw->item(i, j)->setData(Qt::DecorationRole, QPixmap::fromImage(*img).scaled(120, 120));
            }
            else if(c == 'R'){
                QString imgPath = "/home/abc/Desktop/RS/CHESS/images/rook1.png";
                QImage *img = new QImage(imgPath);
                tw->item(i, j)->setData(Qt::DecorationRole, QPixmap::fromImage(*img).scaled(120, 120));
            }
            else if(c == 'n'){
                QString imgPath = "/home/abc/Desktop/RS/CHESS/images/knight.png";
                QImage *img = new QImage(imgPath);
                tw->item(i, j)->setData(Qt::DecorationRole, QPixmap::fromImage(*img).scaled(120, 120));
            }
            else if(c == 'N'){
                QString imgPath = "/home/abc/Desktop/RS/CHESS/images/knight1.png";
                QImage *img = new QImage(imgPath);
                tw->item(i, j)->setData(Qt::DecorationRole, QPixmap::fromImage(*img).scaled(120, 120));
            }
            else if(c == 'b'){
                QString imgPath = "/home/abc/Desktop/RS/CHESS/images/bishop.png";
                QImage *img = new QImage(imgPath);
                tw->item(i, j)->setData(Qt::DecorationRole, QPixmap::fromImage(*img).scaled(120, 120));
            }
            else if(c == 'B'){
                QString imgPath = "/home/abc/Desktop/RS/CHESS/images/bishop1.png";
                QImage *img = new QImage(imgPath);
                tw->item(i, j)->setData(Qt::DecorationRole, QPixmap::fromImage(*img).scaled(120, 120));
            }
            else if(c == 'q'){
                QString imgPath = "/home/abc/Desktop/RS/CHESS/images/queen.png";
                QImage *img = new QImage(imgPath);
                tw->item(i, j)->setData(Qt::DecorationRole, QPixmap::fromImage(*img).scaled(120, 120));
            }
            else if(c == 'Q'){
                QString imgPath = "/home/abc/Desktop/RS/CHESS/images/queen1.png";
                QImage *img = new QImage(imgPath);
                tw->item(i, j)->setData(Qt::DecorationRole, QPixmap::fromImage(*img).scaled(120, 120));
            }
            else if(c == 'k'){
                QString imgPath = "/home/abc/Desktop/RS/CHESS/images/king.png";
                QImage *img = new QImage(imgPath);
                tw->item(i, j)->setData(Qt::DecorationRole, QPixmap::fromImage(*img).scaled(120, 120));
            }
            else if(c == 'K'){
                QString imgPath = "/home/abc/Desktop/RS/CHESS/images/king1.png";
                QImage *img = new QImage(imgPath);
                tw->item(i, j)->setData(Qt::DecorationRole, QPixmap::fromImage(*img).scaled(120, 120));
            }
            else if(c == 'p'){
                QString imgPath = "/home/abc/Desktop/RS/CHESS/images/pawn.png";
                QImage *img = new QImage(imgPath);
                tw->item(i, j)->setData(Qt::DecorationRole, QPixmap::fromImage(*img).scaled(120, 120));
            }
            else if(c == 'P'){
                QString imgPath = "/home/abc/Desktop/RS/CHESS/images/pawn1.png";
                QImage *img = new QImage(imgPath);
                tw->item(i, j)->setData(Qt::DecorationRole, QPixmap::fromImage(*img).scaled(120, 120));
            }
        }
    }
}

MainWindow::MainWindow(QWidget *parent)
 : QMainWindow(parent),
tw(NULL)
{
    tw = new QTableWidget(this);
    tw->setMinimumWidth(960);
    tw->setMinimumHeight(960);
    tw->setRowCount(8);
    tw->setColumnCount(8);
    tw->verticalHeader()->setVisible(false);
    tw->horizontalHeader()->setVisible(false);
    tw->horizontalHeader()->setDefaultSectionSize(120);
    tw->verticalHeader()->setDefaultSectionSize(120);
    tw->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    tw->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    for(int i = 0;i<8;i++) {
        for(int j = 0;j<8;j++) {
            tw->setItem(i, j, new QTableWidgetItem());
            if((i%2 == 0 && j % 2 == 1) || (i % 2 == 1 && j % 2 == 0))
            tw->item(i, j)->setBackgroundColor(Qt::darkGray);


            else if((i %2 == 0 && j %2 == 0) || (i % 2 == 1 && j % 2 == 1))
                tw->item(i, j)->setBackgroundColor(Qt::lightGray);


        }
}





    generateBoard(tw, initial);
    connect(tw, SIGNAL( cellPressed (int, int) ), this, SLOT( cellSelected( int, int ) ) );
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::cellSelected(int x, int y) {
   std::vector<move1> moves;
  // tw->item(x, y)->setSelected(false);


    if(initial.pos[x][y] == 'r' || initial.pos[x][y] == 'R') {
        move1::rook(moves, initial, x, y);
     for(move1 m : moves) {
        std::cout << m.x1 << " " << m.y1 << std::endl;
        tw->item(m.x1, m.y1)->setBackgroundColor(Qt::yellow);
            }
    }


   else if((initial.pos[x][y] == 'n') || (initial.pos[x][y] == 'N')) {
          move1::knight(moves,initial, x, y);
     for(move1 m : moves) {
         std::cout << m.x1 << " " << m.y1 << std::endl;
         tw->item(m.x1, m.y1)->setBackgroundColor(Qt::yellow);
             }

    }

  else  if(initial.pos[x][y] == 'b' || initial.pos[x][y] == 'B') {
         move1::bishop(moves, initial, x, y);
    for(move1 m : moves) {
        std::cout << m.x1 << " " << m.y1 << std::endl;
        tw->item(m.x1, m.y1)->setBackgroundColor(Qt::yellow);
            }
    }


   else if(initial.pos[x][y] == 'q' || initial.pos[x][y] == 'Q') {
          move1::queen(moves, initial, x, y);
     for(move1 m : moves) {
         std::cout << m.x1 << " " << m.y1 << std::endl;
         tw->item(m.x1, m.y1)->setBackgroundColor(Qt::yellow);
             }

    }

   else if(initial.pos[x][y] == 'k' || initial.pos[x][y] == 'K') {
         move1::king(moves,initial, x, y);
    for(move1 m : moves) {
        std::cout << m.x1 << " " << m.y1 << std::endl;
        tw->item(m.x1, m.y1)->setBackgroundColor(Qt::yellow);
            }
    }


   else if(initial.pos[x][y] == 'p' || initial.pos[x][y] == 'P') {
          move1::pawn(moves, initial, x, y);
    for(move1 m : moves) {
         std::cout << m.x1 << " " << m.y1 << std::endl;
         tw->item(m.x1, m.y1)->setBackgroundColor(Qt::yellow);
             }
     }

}
