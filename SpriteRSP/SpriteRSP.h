//
// Created by yangheechan on 2020-12-17.
//
#ifndef SPRITERSP_SPRITERSP_H
#define SPRITERSP_SPRITERSP_H

#include <QMainWindow>
#include <QTimer>
#include <memory>
#include <QVector>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QLabel>
#include <QPixmap>
#include <QPushButton>

namespace Ui {
class SpriteRSP;
}

enum class rsc{PAPER,ROCK,SCISSOR};

class Sprite {
public:
    explicit Sprite(QSize winsize, QByteArray data);
    void Draw(QLabel* painter);
    void NextFrame();
    rsc getCurrentFrame() const;
    void addWin() {win++;};
    void addlose() {lose++;};
    void adddraw() {draw++;};
    double getWinRate();
private:
    std::unique_ptr<QPixmap> SpriteImage;
    int CurrentFrame;
    int TotalFrame;
    int Column;
    int FramesizeX;
    int FramesizeY;
    QPoint FramePosition;
    QPoint DrawPosition;
    unsigned int win;
    unsigned int lose;
    unsigned int draw;
    double winRate;
};

class SpriteRSP : public QMainWindow {
Q_OBJECT
public:
    explicit SpriteRSP(QWidget* parent);
    ~SpriteRSP() override;
    void update();
public slots:
    void replyFinished(QNetworkReply* reply);
    void slot_btnClick();
private:
    std::unique_ptr<Ui::SpriteRSP> ui;
    std::unique_ptr<QNetworkAccessManager> m_netwManger;
    std::unique_ptr<Sprite> sprite;
    std::unique_ptr<QTimer> m_timer;
    QVector<QPushButton*> btns;
    bool imageLoading;
};

#endif //SPRITERSP_SPRITERSP_H
