//
// Created by heechan on 21. 1. 9..
//
#include <QPainter>
#include <QSizePolicy>
#include "mainWindow.h"
#include "ui_main.h"
#include <QDebug>
#include <QTimer>

mainWindow::mainWindow(QMainWindow* parent)
        :QMainWindow(parent),
         ui(std::make_unique<Ui::MainWindow>()),
         isLoading(false),
         style("QLabel { border: 1px solid white;"
               "            border-radius: 20px;"
               "            width: 40px;"
               "            height: 40px;"
               "            line-height: 40px;"
               "            font-size: 25px;"
               "min-height: 40px; min-width: 40px;"
               "            text-align: right;"
               "            margin-right: 20px;}")
{
    ui->setupUi(this);

    Rotto.init(); // 데이터 생성
    init(); // 초기화
    printUsingData(); //출력

    connect(ui->pushButton, &QPushButton::clicked, this, &mainWindow::onClickButton);
}

mainWindow::~mainWindow()
{
}

//공 모양으로 초기화
void mainWindow::init()
{
    // initialize bonus && Balls
    auto ctw = ui->centralwidget->children();
            foreach(QObject* obj, ctw) {
            QLabel* label = qobject_cast<QLabel*>(obj);
            if (label) {
                if (label->text()==QString("TextLabel")) {
                    label->setStyleSheet(style);
                    label->setText("");
                    label->setMaximumWidth(40);
                    label->hide();
                }
            }
        }

//    ui->horizontalLayout->itemAt(1)->widget()->hide();

    ui->bonus->setStyleSheet(style);
    ui->bonus->setText("");
    ui->bonus->hide();
}

void mainWindow::onClickButton()
{
    // 애니메이션 진행중이면 클릭 금지
    if (isLoading) return;

    Rotto.init(); // 데이터 재생성
    hideBalls();
    printUsingData();

    qDebug() << "버튼클릭됨";
}

void mainWindow::printUsingData()
{
    isLoading = true;
    auto nums = Rotto.getNumbers();
    auto bonus = Rotto.getBonus();
    int index = 0;

    auto ctw = ui->centralwidget->children();
            foreach(QObject* obj, ctw) {
            auto* label = qobject_cast<QLabel*>(obj);
            if (label) {
                // 이름으로 참조
                if (label->objectName()[0]=="w") {
                    int winNum = nums[index];
                    QTimer::singleShot(1000*index, this, [&, winNum, label]() {
                        label->show();
                        label->setText(QString::number(winNum));
                        label->setStyleSheet(style+selectStyle(winNum));
                    });
                    index++;
                }
            }
        }
    QTimer::singleShot(1000*index, this, [&, bonus]() {
        isLoading = false;
        ui->bonus->setText(QString::number(bonus));
        ui->bonus->show();
        ui->bonus->setStyleSheet(style+ selectStyle(bonus));
    });
}

void mainWindow::hideBalls()
{
    auto ctw = ui->centralwidget->children();
            foreach(QObject* obj, ctw) {
            QLabel* label = qobject_cast<QLabel*>(obj);
            if (label) {
                if (label->objectName()[0]=="w") {
                    label->hide();
                }
            }
        }
    ui->bonus->hide();
}

QString mainWindow::selectStyle(int num)
{
    if (num<11) {
        return QString("QLabel{background-color: yellow; color:black;}");
    }
    else if (num<21) {
        return QString("QLabel{background-color: blue; color:white;}");
    }
    else if (num<31) {
        return QString("QLabel{background-color: red; color:white;}");
    }
    else if (num<41) {
        return QString("QLabel{background-color: gray; color:white;}");
    }
    else {
        return QString("QLabel{background-color: green; color:white;}");
    }
}
