#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QTableWidget"
#include "board.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void generateBoard(board &b);
    void resetColors();
    void setHighlight(int x, int y);

private slots:

void cellSelected(int nRow, int nCol);

private:
Ui::MainWindow *ui;
QTableWidget* tw;

QStringList m_TableHeader;

};

#endif // MAINWINDOW_H
