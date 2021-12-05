#include "startmenu.h"
#include "ui_startmenu.h"
#include "mainwindow.h"
#include <QDebug>

StartMenu::StartMenu(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::StartMenu)
{
    ui->setupUi(this);
}

StartMenu::~StartMenu() {
    delete ui;
}

void StartMenu::on_exit_clicked()
{
    close();
}

void StartMenu::on_startgame_clicked()
{
    MainWindow *mainwindow = new MainWindow(this);
    mainwindow->setAttribute(Qt::WA_DeleteOnClose);
    mainwindow->show();
    hide();
}
