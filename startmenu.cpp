#include "startmenu.h"
#include "ui_startmenu.h"
#include "mainwindow.h"
#include "loadsave.h"
#include <QDebug>
#include <QDialog>

StartMenu::StartMenu(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::StartMenu)
{
    ui->setupUi(this);
}

StartMenu::~StartMenu() {
    delete ui;
}

void StartMenu::StartGame() {
    MainWindow *mainwindow = new MainWindow(this);
    mainwindow->setAttribute(Qt::WA_DeleteOnClose);
    mainwindow->setWindowModality(Qt::ApplicationModal);
    mainwindow->show();
}

void StartMenu::on_exit_clicked()
{
    close();
}

void StartMenu::on_startgame_clicked()
{
    StartGame();
    //hide();
}

void StartMenu::on_loadsaves_clicked()
{
    LoadSave *loadsave = new LoadSave(this);
    loadsave->setWindowFlag(Qt::Window);
    loadsave->setAttribute(Qt::WA_DeleteOnClose);
    loadsave->setWindowModality(Qt::ApplicationModal);
    loadsave->show();
    //hide();
}
