#include <QApplication>

#include "Headers/GUI/mainwindow.h"
#include "Headers/GUI/startmenu.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    StartMenu w;
    w.show();
    return a.exec();
}
