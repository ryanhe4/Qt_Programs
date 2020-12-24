//
// Created by yangheechan on 2020-12-20.
//
#include "MainWindow.h"
#include "ui_tictactoe.h"
#include <QDebug>
#include <QTimer>
#include <memory>

MainWindow::~MainWindow() noexcept
{
    ui->tableWidget->clear();
}
MainWindow::MainWindow(QMainWindow* parent)
        :QMainWindow(parent),
         ui(std::make_unique<Ui::MainWindow>()),
         tic(std::make_unique<TicTacToe>())
{
    ui->setupUi(this);

    settingTable();
    init();

    connect(ui->tableWidget, &QTableWidget::cellClicked, this, &MainWindow::slot_clicked);
}
//Setting 과 init을 구별
void MainWindow::settingTable()
{
    ui->tableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->tableWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->horizontalHeader()->hide();
    ui->tableWidget->verticalHeader()->hide();
    ui->tableWidget->setRowCount(3);
    ui->tableWidget->setColumnCount(3);

    // QTableWidget 생성 -> 테이블에 할당, 생성된 객체는 소멸자에서 clear() 호출시 일괄 삭제된다.
    for (int i = 0; i<3; i++) {
        for (int j = 0; j<3; j++) {
            auto obj = std::make_unique<QTableWidgetItem>();
            obj->setTextAlignment(Qt::AlignCenter);
            ui->tableWidget->setItem(i, j, obj.get());

            item.emplace_back(std::move(obj));
        }
    }
}

void MainWindow::init()
{
    //Ui데이터 초기화
    for (int i = 0; i<3; i++) {
        for (int j = 0; j<3; j++) {
            ui->tableWidget->item(i, j)->setText("");
            ui->tableWidget->item(i, j)->setBackground(QColor(204, 204, 204));
        }
    }
    ui->label->setText("X의 턴");
    //tic 내부 데이터 초기화
    tic->init();
    state = 0;
}

void MainWindow::slot_clicked(int row, int col)
{
    if (state==1) return;

    if (tic->confirmData(row, col).empty()) { //칸에 아무것도 없으면(이전에 클릭이 안됐으면
        QString t = QString::fromUtf8(tic->getTurn().c_str()); // 현재 턴

        tic->setData(row, col);
        ui->tableWidget->item(row, col)->setText(t);

        if (tic->CheckResult()) {
            auto Point = tic->getWinPoint();
            for (auto& elem : Point) {
                ui->tableWidget->item(elem.first, elem.second)->setBackground(QColor(60, 179, 113));
                ui->tableWidget->item(row, col)->setFlags(Qt::ItemIsEnabled);
            }
            ui->label->setText(t+"의 승리! 잠시 후 다시 시작합니다.");
            state = 1;

            QTimer::singleShot(3*1000, this, &MainWindow::init);
        }
        else {
            //TODO 모든칸이 채워졌는지 확인
            if (tic->CheckFull()) {
                ui->label->setText("[비김!] 잠시 후 다시 시작합니다.");
                state = 1;

                QTimer::singleShot(3*1000, this, &MainWindow::init);
            }
            else {
                //TODO 라벨에 턴표시
                tic->toggleTurn();
                t = QString::fromUtf8(tic->getTurn().c_str()); // 현재 턴
                ui->label->setText(t+"의 턴");
                if (t=="O") {
                    auto p = tic->coordinates();
                    qDebug() << p.first << p.second;
                    QTimer::singleShot(1*1000, this, [&, p]() {
                      state = 0;
                      slot_clicked(p.first, p.second);
                    });
                    state = 1;
                }
            }
        }

    }
}
