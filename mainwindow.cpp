#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "event.h"

QTextCodec *codec = QTextCodec::codecForName("GBK");

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    optionNum = 0;
    buttonsLayout = nullptr;
    initButtons();
    initController();
    initAttrTable();
    flush();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initController() {
    controller = new Controller();
    QObject::connect(this, &MainWindow::buttonClicked, controller, &Controller::run);
    controller->init();
}

void MainWindow::flush() {
    if (!loadCurrentEvent()) return;
    setText(this->controller->getCurrentEvent().getText() + '\n');
}

void MainWindow::setText(const std::string& text) {
    std::string message = text;
    //qDebug() << message.c_str();
    ui->textBrowser->insertPlainText(codec->toUnicode(message.c_str()));
    ui->textBrowser->moveCursor(QTextCursor::End);
}

void MainWindow::initAttrTable() {

}

void MainWindow::initButtons() {
    qDebug() << "Init buttons...";

    buttonsLayout = new QVBoxLayout(ui->buttons);
    buttonsLayout->setDirection(QVBoxLayout::TopToBottom);
    for(int i = 0; i < MAX_OPTION_NUM; i++) {
        buttons[i] = new QPushButton("...");
        buttonsLayout->addWidget(buttons[i], 1);
    }
    ui->buttons->setLayout(buttonsLayout);

    QObject::connect(buttons[0], &QPushButton::clicked, this, &MainWindow::emitButtonClicked0);
    QObject::connect(buttons[1], &QPushButton::clicked, this, &MainWindow::emitButtonClicked1);
    QObject::connect(buttons[2], &QPushButton::clicked, this, &MainWindow::emitButtonClicked2);
    QObject::connect(buttons[3], &QPushButton::clicked, this, &MainWindow::emitButtonClicked3);
    QObject::connect(buttons[4], &QPushButton::clicked, this, &MainWindow::emitButtonClicked4);

    qDebug() << "Done.";
}

bool MainWindow::loadCurrentEvent() {
    if (!controller || !controller->isReady()) return false;

    Event event = controller->getCurrentEvent();

    qDebug() << "Changing buttons' status...";
    optionNum = event.optionSet.size();
    for (int i = 0; i < optionNum; i++) {
        buttons[i]->setText(event.optionSet.findOption(i)->second.c_str());
        buttons[i]->setDisabled(false);
    }
    for (int i = optionNum; i < MAX_OPTION_NUM; i++) {
        buttons[i]->setText("");
        buttons[i]->setDisabled(true);
    }

    return true;
}
