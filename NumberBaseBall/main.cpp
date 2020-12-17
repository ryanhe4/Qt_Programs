#include <QApplication>
#include "NumberBaseBall.h"

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    NumberBaseBall number_base_ball(nullptr);
    number_base_ball.show();

    return QApplication::exec();
}
