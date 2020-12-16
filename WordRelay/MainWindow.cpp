//
// Created by yangheechan on 2020-12-15.
//
#include "MainWindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QMainWindow* parent)
        :QMainWindow(parent),
         ui(new Ui::MainWindow),
         message_box(new QMessageBox(this))
{
    ui->setupUi(this);
    ui->lb1->setText("시작단어");
    ui->lE1->setText("");

    message_box->setText("땡!!");

    connect(ui->btn1, &QPushButton::clicked, this, &MainWindow::slot_btn);
}

MainWindow::~MainWindow() noexcept
{
    delete ui;
    delete message_box;
}
void MainWindow::slot_btn()
{
    // get quest and answer text
    QString questionWord = ui->lb1->text();
    QString answerWord = ui->lE1->text();

    // check
    if (questionWord[questionWord.size()-1]==answerWord[0]) {
        ui->lb1->setText(answerWord);
        ui->lE1->setText("");
    }
    else {
        message_box->show();

        ui->lE1->setText("");
    }
}

void MainWindow::keyPressEvent(QKeyEvent* event)
{   // keyBoard Enter Click
    switch (event->key()) {
    case Qt::Key_Return: ui->btn1->click();
        break;
    }
}

