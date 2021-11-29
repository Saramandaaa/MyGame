#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    controller = new Controller();
    QObject::connect(this, &MainWindow::buttonClicked, controller, &Controller::run);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::flush() {
    this->setText(this->controller->getCurrentEvent().getText());
}

void MainWindow::setText(const std::string& text) {
    ui->label->setText(text.c_str());
}
