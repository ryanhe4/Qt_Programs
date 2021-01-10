//
// Created by heechan on 21. 1. 9..
//

#ifndef ROTTO_MAINWINDOW_H
#define ROTTO_MAINWINDOW_H

#include <QMainWindow>
#include <memory>
#include "state.h"

namespace Ui {
    class MainWindow;
}

class mainWindow : public QMainWindow {
Q_OBJECT
public:
    explicit mainWindow(QMainWindow* parent);
    ~mainWindow() override;

    void printUsingData();
    void hideBalls();
private:
    std::unique_ptr<Ui::MainWindow> ui;
    bool isLoading;
    state Rotto;
    void init(); // initialize
    QString style;
    static QString selectStyle(int num);
public slots:
    void onClickButton();
};

#endif //ROTTO_MAINWINDOW_H
