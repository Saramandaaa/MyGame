#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    //QPushButton but("+1s", &w);
    //but.setGeometry(350, 500, 100, 30);

    //EventOption op1(&but, 0);
    //op1.setConnection();
    //QObject::connect(&op1, &EventOption::choose, &w, &MainWindow::emitButtonClicked);

    w.show();
    return a.exec();
}
