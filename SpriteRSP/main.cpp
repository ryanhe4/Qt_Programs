#include <QApplication>
#include "SpriteRSP.h"


int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    SpriteRSP app(nullptr);
    app.show();
    return QApplication::exec();
}
