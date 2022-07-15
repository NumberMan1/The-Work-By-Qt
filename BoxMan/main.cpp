#include "BoxMan.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    try {
        QApplication a(argc, argv);
        BoxMan w;
        w.show();
        return a.exec();
    } catch (...) {
        QApplication a(argc, argv);
        QErrorMessage err;
        err.showMessage("Unknown Error");
        return err.exec();
    }
}
