#include <QDebug>
#include <QDialog>

#include "ui_startmenu.h"
#include "Headers/GUI/startmenu.h"
#include "Headers/GUI/mainwindow.h"
#include "Headers/GUI/loadsave.h"

StartMenu::StartMenu(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::StartMenu)
{
    ui->setupUi(this);
}

StartMenu::~StartMenu() {
    delete ui;
}

void StartMenu::startGame(bool from_save) {
    if (from_save) {
        MainWindow *mainwindow = new MainWindow(info, this);
        mainwindow->setAttribute(Qt::WA_DeleteOnClose);
        mainwindow->setWindowModality(Qt::ApplicationModal);
        mainwindow->show();
    }
    else {
        MainWindow *mainwindow = new MainWindow(this);
        mainwindow->setAttribute(Qt::WA_DeleteOnClose);
        mainwindow->setWindowModality(Qt::ApplicationModal);
        mainwindow->show();
    }
}

void StartMenu::setInfo(SaveInfo in) {
    info = in;
}

SaveInfo StartMenu::getInfo() {
    return info;
}

void StartMenu::on_exit_clicked() {
    close();
}

void StartMenu::on_startgame_clicked() {
    startGame();
    //hide();
}

void StartMenu::on_loadsaves_clicked() {
    LoadSave *loadsave = new LoadSave(this);
    loadsave->setWindowFlag(Qt::Window);
    loadsave->setAttribute(Qt::WA_DeleteOnClose);
    loadsave->setWindowModality(Qt::ApplicationModal);
    QObject::connect(loadsave, &LoadSave::save_info_loaded, this, &StartMenu::continue_from_save);
    loadsave->show();
    //hide();
}

void StartMenu::continue_from_save(SaveInfo in) {
    setInfo(in);
    startGame(true);
}
