//
// Created by yangheechan on 2020-12-20.
//
#ifndef TICTACTOE_MAINWINDOW_H
#define TICTACTOE_MAINWINDOW_H
#include <QMainWindow>
#include <memory>
#include <QTableWidgetItem>
#include "TicTacToe.h"
#include "vector"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
Q_OBJECT
public:
    explicit MainWindow(QMainWindow* parent);
    ~MainWindow() override;
public slots:
    void slot_clicked(int row, int col);
private:
    std::unique_ptr<Ui::MainWindow> ui;
    std::unique_ptr<TicTacToe> tic;
    std::vector<std::unique_ptr<QTableWidgetItem>> item;
    int state = 0;

    void settingTable();
    void init();
};

#endif //TICTACTOE_MAINWINDOW_H
