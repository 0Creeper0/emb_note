#include "nettalk.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Nettalk w;
    w.setWindowTitle("欢迎使用");
    w.show();

    return a.exec();
}
