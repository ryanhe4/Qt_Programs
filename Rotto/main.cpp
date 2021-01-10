#include <QApplication>

#include "mainWindow.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    mainWindow main(nullptr);
    main.show();

    return QApplication::exec();
}
