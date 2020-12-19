//
// Created by yangheechan on 2020-12-17.
//
#include "ui_mainwindow.h"
#include "SpriteRSP.h"
#include <QMessageBox>

SpriteRSP::SpriteRSP(QWidget* parent)
        :QMainWindow(parent),
         ui(new Ui::SpriteRSP),
         m_netwManger(new QNetworkAccessManager(this)),
         m_timer(new QTimer()),
         imageLoading(false)
{
    ui->setupUi(this);

    QString btn_str[3] = {"가위", "바위", "보"};

    ui->winRate->setText("승률 : 0%");

    //pushButton_3 : 가위 | 2: 바위 | 1: 보
    btns.push_back(ui->pushButton_3);
    btns.push_back(ui->pushButton_2);
    btns.push_back(ui->pushButton);

    // 버튼 이벤트 생성
    for (int i = 0; i<btns.length(); ++i) {
        btns[i]->setText(btn_str[i]);
        connect(btns[i], &QPushButton::clicked, this, &SpriteRSP::slot_btnClick);
    }

    //네트워크 이벤트
    connect(m_netwManger.get(), &QNetworkAccessManager::finished, this, &SpriteRSP::replyFinished);
    connect(m_timer.get(), &QTimer::timeout, this, &SpriteRSP::update);

    m_netwManger->get(QNetworkRequest(QUrl("http://en.pimg.jp/023/182/267/1/23182267.jpg")));
    m_timer->start(100);
}
SpriteRSP::~SpriteRSP()
{
}

void SpriteRSP::replyFinished(QNetworkReply* reply)
{
    auto data = reply->readAll();
    sprite = std::make_unique<Sprite>(size(), std::move(data));
    imageLoading = true;
}

void SpriteRSP::update()
{
    // 해당 함수가 동작할 조건 정의
    sprite->Draw(ui->label);
    sprite->NextFrame();
}
void SpriteRSP::slot_btnClick()
{
    //imageLoading 안됐을 경우 실패
    if (!imageLoading) return;

    // 타이머 정지, 메시지 박스 => 메시지 확인시에 타이머 다시 기동
    m_timer->stop();

    auto* buttonSender = qobject_cast<QPushButton*>(sender());
//    qDebug() << buttonSender->text();

    const rsc enemyVal = sprite->getCurrentFrame();
    rsc myVal;

    if (buttonSender->text()=="가위") myVal = rsc::SCISSOR;
    else if (buttonSender->text()=="바위") myVal = rsc::ROCK;
    else myVal = rsc::PAPER;

    // 승/패 조건
    if (myVal==enemyVal) {
        if (QMessageBox::information(this, "메시지박스", "비겼습니다")) {
            // 비김 추가
            sprite->adddraw();
            ui->winRate->setText("승률 : "+QString::number(sprite->getWinRate()*100)+"%");
            m_timer->start(100);
        }
    }
    else {
        const int i_myVal = static_cast<int>(myVal);
        const int i_enemyVal = static_cast<int>(enemyVal);

        const int penalty = i_myVal-i_enemyVal;

        if (penalty==-1 || penalty==2) {
            //승
            if (QMessageBox::information(this, "메시지박스", "승")) {
                sprite->addWin();
                ui->winRate->setText("승률 : "+QString::number(sprite->getWinRate()*100)+"%");
                m_timer->start(100);
            }
        }
        else if (penalty==-2 || penalty==1) {
            //패
            if (QMessageBox::information(this, "메시지박스", "패")) {
                sprite->addlose();
                ui->winRate->setText("승률 : "+QString::number(sprite->getWinRate()*100)+"%");
                m_timer->start(100);
            }
        }
    }
}

Sprite::Sprite(QSize winsize, QByteArray data)
        :CurrentFrame(0), TotalFrame(3), Column(3),
         FramesizeX(142), FramesizeY(220),
         FramePosition(0, 0),
         SpriteImage(new QPixmap()),
         win(0), draw(0), lose(0), winRate(0)
{
//    qDebug() << "MainWindow Size: " << MainWindowSize << "\n";
    SpriteImage->loadFromData(data);

//    qDebug() << "Sprite Size: " << SpriteImage->size() << "\n";

    DrawPosition.setX(0);
    DrawPosition.setY(0);
}

void Sprite::Draw(QLabel* painter)
{
    QRect rect(FramePosition.x(), FramePosition.y(), FramesizeX, FramesizeY);
    QPixmap cropped = SpriteImage->copy(rect);
    painter->setPixmap(cropped);
}

void Sprite::NextFrame()
{
    if (CurrentFrame>=TotalFrame)
        CurrentFrame = 0;

    FramePosition.setX((CurrentFrame%Column)*FramesizeX);
    FramePosition.setY(0);

    CurrentFrame++;
}
rsc Sprite::getCurrentFrame() const
{
    switch (CurrentFrame-1) {
    case 0: return rsc::PAPER;
    case 1: return rsc::ROCK;
    case 2: return rsc::SCISSOR;
    default:throw std::out_of_range("out of range");
    }
}
double Sprite::getWinRate()
{
    const double total = win+lose+draw;
    winRate = win/total;
    return winRate;
}
