#include "choosepan.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ChoosePan w;
    w.show();

    return a.exec();
}
