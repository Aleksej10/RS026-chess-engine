#include "mainwindow.h"

#include <QApplication>
#include <QDesktopWidget>
#include <QCoreApplication>
#include <QHeaderView>
#include <QMessageBox>
#include "board.h"
#include <vector>
 

board initial("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");

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
       moves =  move1::rook(initial, x, y);
     for(move1 m : moves) {
        std::cout << m.x1 << " " << m.y1 << std::endl;
        tw->item(m.x1, m.y1)->setBackgroundColor(Qt::yellow);
            }
    }


   else if(initial.pos[x][y] == 'n' || initial.pos[x][y] == 'n') {
        moves =  move1::knight(initial, x, y);
     for(move1 m : moves) {
         std::cout << m.x1 << " " << m.y1 << std::endl;
         tw->item(m.x1, m.y1)->setBackgroundColor(Qt::yellow);
             }

    }

  else  if(initial.pos[x][y] == 'b' || initial.pos[x][y] == 'B') {
       moves =  move1::bishop(initial, x, y);
    for(move1 m : moves) {
        std::cout << m.x1 << " " << m.y1 << std::endl;
        tw->item(m.x1, m.y1)->setBackgroundColor(Qt::yellow);
            }
    }


   else if(initial.pos[x][y] == 'q' || initial.pos[x][y] == 'Q') {
        moves =  move1::queen(initial, x, y);
     for(move1 m : moves) {
         std::cout << m.x1 << " " << m.y1 << std::endl;
         tw->item(m.x1, m.y1)->setBackgroundColor(Qt::yellow);
             }

    }

   else if(initial.pos[x][y] == 'k' || initial.pos[x][y] == 'K') {
       moves =  move1::king(initial, x, y);
    for(move1 m : moves) {
        std::cout << m.x1 << " " << m.y1 << std::endl;
        tw->item(m.x1, m.y1)->setBackgroundColor(Qt::yellow);
            }
    }


   else if(initial.pos[x][y] == 'p' || initial.pos[x][y] == 'P') {
        moves =  move1::pawn(initial, x, y);
    for(move1 m : moves) {
         std::cout << m.x1 << " " << m.y1 << std::endl;
         tw->item(m.x1, m.y1)->setBackgroundColor(Qt::yellow);
             }
     }



}
