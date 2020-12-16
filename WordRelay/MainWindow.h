//
// Created by yangheechan on 2020-12-15.
//
#ifndef IMAGESPRITE_MAINWINDOW_H
#define IMAGESPRITE_MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QMessageBox>
#include <QKeyEvent>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QMainWindow *parent = nullptr);
    ~MainWindow();

    virtual void keyPressEvent(QKeyEvent *event);

public slots: // One of EventHandller
    void slot_btn();
private:
    Ui::MainWindow *ui;
    QMessageBox *message_box;

};

#endif //IMAGESPRITE_MAINWINDOW_H
