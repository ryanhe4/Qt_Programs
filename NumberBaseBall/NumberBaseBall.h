//
// Created by yangheechan on 2020-12-16.
//

#ifndef NUMBERBASEBALL_NUMBERBASEBALL_H
#define NUMBERBASEBALL_NUMBERBASEBALL_H

#include <QMainWindow>
#include <QRegExpValidator>
#include <memory>
#include <QMessageBox>
#include <QLineEdit>
#include <QKeyEvent>

namespace Ui {
class NumberBaseBall;
}

class NumberBaseBall : public QMainWindow {
Q_OBJECT
public:
    explicit NumberBaseBall(QMainWindow* parent);
    ~NumberBaseBall();

    void keyPressEvent(QKeyEvent* event) override;
public slots:
    void slot_btnClick();
    void slot_changeText(const QString &text);
private:
    std::unique_ptr<Ui::NumberBaseBall> ui;
    std::unique_ptr<QRegExpValidator> rxv;
    std::unique_ptr<QMessageBox> m_box;

    QString m_input;
    QString m_answer;
    int m_numberOfAttempts;
    void CreateAnswerData();
};

#endif //NUMBERBASEBALL_NUMBERBASEBALL_H
