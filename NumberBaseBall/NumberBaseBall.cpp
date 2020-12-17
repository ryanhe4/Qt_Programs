//
// Created by yangheechan on 2020-12-16.
//
#include "NumberBaseBall.h"
#include <random>
#include <QDebug>
#include "ui_mainwindow.h"

NumberBaseBall::NumberBaseBall(QMainWindow* parent)
        :QMainWindow(parent),
         ui(new Ui::NumberBaseBall),
         m_input(""),
         m_answer(""),
         rxv(new QRegExpValidator(QRegExp("[+-]?\\d*"), this)),
         m_box(new QMessageBox(this)),
         m_numberOfAttempts(0)
{
    ui->setupUi(this);

    ui->lE1->setText("");
    ui->lE1->setValidator(rxv.get());

    CreateAnswerData(); // 상태 초기화

    //버튼 및 LineEdit Event Bind
    connect(ui->btn1, &QPushButton::clicked, this, &NumberBaseBall::slot_btnClick);
    connect(ui->lE1, &QLineEdit::textChanged, this, &NumberBaseBall::slot_changeText);
}

//초기화 함수
void NumberBaseBall::CreateAnswerData()
{
    std::random_device rd;

    QVector<int> shuffle(10);

    std::iota(shuffle.begin(), shuffle.end(), 0);
    std::shuffle(shuffle.begin(), shuffle.end(), std::mt19937{rd()});

    m_answer = "";

    // 셔플 앞 4개 숫자 선택
    for (int i = 0; i<4; ++i) {
        m_answer.push_back(QString::number(shuffle[i]));
    }

    // 시도횟수 초기화
    m_numberOfAttempts = 0;

    qDebug() << m_answer;
}

void NumberBaseBall::slot_btnClick()
{
    auto LineText = ui->lE1->text();

    // Basic input Error handling
    if (LineText.length()!=4) {
        m_box->setWindowTitle("Error!");
        m_box->setText("4자리 숫자만 입력 가능합니다.");
        m_box->show();
        return;
    }

    if (m_input==m_answer) {
        //정답 메시지 출력 + 초기화
        ui->lb1->setText("홈런!!!");
        ui->lE1->setText("");
        ui->lE1->setFocus();
        CreateAnswerData();
    }
    else {
        // 정답 아님, count가 10회를 넘어가는 경우 정답 출력 + 초기화
        int maxAttemps = 10;
        m_numberOfAttempts++;

        // 카운트가 10회가 넘었을 경우
        if (m_numberOfAttempts>maxAttemps) {
            QString msg("10회 틀려서 실패 정답은"+m_answer+"이었습니다!!");
            ui->lb1->setText(msg);
            ui->lE1->setText("");
            ui->lE1->setFocus();
            CreateAnswerData();

            return;
        }
        else {
            int strike = 0;
            int ball = 0;

            // 스트라이크, 볼 계산
            for (int i = 0; i<4; i++) {
                if (m_input[i]==m_answer[i]) {
                    strike++;
                }
                else {
                    if (m_answer.contains(m_input[i])) {
                        ball++;
                    }
                }
            }

            auto msg = QString("%1 스트라이크 %2 볼 입니다.").arg(strike).arg(ball);
            ui->lb1->setText(msg);
            ui->lE1->setText("");
            ui->lE1->setFocus();
        }

    }

}

//changeEvent(signal)로 m_input[data]와 lineEdit(view)값 동기화
void NumberBaseBall::slot_changeText(const QString& text)
{
    m_input = text;
}

void NumberBaseBall::keyPressEvent(QKeyEvent* event)
{
    Q_UNUSED(event);
    if(event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) {
        ui->btn1->click();
    }
}
NumberBaseBall::~NumberBaseBall()
{

}
