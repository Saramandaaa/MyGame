#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "event.h"
#include "eventoption.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QPointer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    optionNum = 0;
    options = nullptr;
    //setFixedSize(ui->centralwidget->width(), ui->centralwidget->height());
    initController();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initController() {
    controller = new Controller();
    QObject::connect(this, &MainWindow::buttonClicked, controller, &Controller::run);
}

void MainWindow::flush() {
    if (!loadCurrentEvent()) return;
    setText(this->controller->getCurrentEvent().getText());
}

void MainWindow::setText(const std::string& text) {
    ui->textBrowser->append(text.c_str());
    ui->textBrowser->moveCursor(QTextCursor::End);
}

bool MainWindow::linkButtons() {
    for (int i = 0; i < optionNum; i++) {
        QObject::connect(&options[i], &EventOption::choose, this, &MainWindow::emitButtonClicked);
    }
    return true;
}

bool MainWindow::loadCurrentEvent() {
    if (!controller || !controller->isReady()) return false;

    for (int i = 0; i < optionNum; i++)
        options[i].removeConnection();
    delete [] options;

    Event event = controller->getCurrentEvent();
    QVBoxLayout *buttonsLayout = ui->buttonsLayout;
    buttonsLayout->setDirection(QVBoxLayout::TopToBottom);
    QLayoutItem *child;
    while(child = buttonsLayout->takeAt(0))
        delete child;

    optionNum = event.optionSet.size();
    options = new EventOption [optionNum];
    for (int i = 0; i < optionNum; i++) {
        QPointer<QPushButton> but = new QPushButton(event.optionSet.findOption(i)->second.c_str());
        buttonsLayout->addWidget(but, 1);
        options[i].button = but;
        options[i].id = i;
        options[i].setConnection();
    }

    setLayout(buttonsLayout);
    return linkButtons();
}
