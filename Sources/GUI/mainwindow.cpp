#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "event.h"
#include "loadsave.h"
#include "textcode.h"
#include "eventlist.h"
#include <QCloseEvent>
#include <QMenu>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    optionNum = 0;
    gameEndFlag = false;
    buttonsLayout = nullptr;
    initButtons();
    initController();
    initAttrTable();
    initMenuBar();
    flush();
    qDebug() << "Initialization End.";
}

MainWindow::MainWindow(SaveInfo info, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    optionNum = 0;
    gameEndFlag = false;
    buttonsLayout = nullptr;
    initButtons();
    initController();
    initAttrTable();
    initMenuBar();
    initFromSaveInfo(info);
    qDebug() << "Initialization From Save End.";
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initMenuBar() {

}

void MainWindow::gameEnd(EventEnum) {
    setText("游戏结束...");
    gameEndFlag = true;
    buttons[0]->setText(codec->toUnicode("保存结果"));
    for (int i = 1; i < MAX_OPTION_NUM; i++) {
        buttons[i]->setText("");
        buttons[i]->setDisabled(true);
    }
    QObject::connect(buttons[0], &QPushButton::clicked, this, &MainWindow::on_actionsave_triggered);
}

void MainWindow::initController() {
    qDebug() << "Init controller...";
    controller = new Controller();
    QObject::connect(this, &MainWindow::buttonClicked, controller, &Controller::run);
    controller->init();
}

void MainWindow::initFromSaveInfo(SaveInfo info) {
    EventList::load(info);
    controller->setMainCharacter(info.attribute);
    controller->setCurrentEvent(EventList::getEvent(info.eventType));
    ui->textBrowser->setText(info.message.c_str());
    ui->textBrowser->moveCursor(QTextCursor::End);
    if (!loadCurrentEvent()) {
        qDebug() << "loadCurrentEvent Error!";
        return;
    }
    flushTable();
}

void MainWindow::flush() {
    if (gameEndFlag) return;
    if (!loadCurrentEvent()) {
        qDebug() << "loadCurrentEvent Error!";
        return;
    }
    setText(this->controller->getCurrentEvent()->getText() + '\n');
    flushTable();
}

void MainWindow::setText(const std::string& text) {
    std::string message = text;
    //qDebug() << message.c_str();
    ui->textBrowser->insertPlainText(codec->toUnicode(message.c_str()));
    ui->textBrowser->moveCursor(QTextCursor::End);
}

std::string MainWindow::getText() {
    return ui->textBrowser->toPlainText().toStdString();
}

void MainWindow::initAttrTable() {
    qDebug() << "Init attributes table...";
    table = ui->attributes;
    int n = 9, m = 2;
    table->setColumnCount(m);
    table->setColumnWidth(0, table->width() / 3.0 * 2.0);
    table->setColumnWidth(1, table->width() - table->width() / 3.0 * 2.0);
    table->setRowCount(n);
    for (int i = 0; i < n; i++)
        table->setRowHeight(i, table->height() / n);
    table->horizontalHeader()->hide();
    table->verticalHeader()->hide();
    table->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    table->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    table->setItem(0, 0, new QTableWidgetItem(codec->toUnicode("学期数")));
    table->setItem(1, 0, new QTableWidgetItem(codec->toUnicode("身体素质")));
    table->setItem(2, 0, new QTableWidgetItem(codec->toUnicode("压力")));
    table->setItem(3, 0, new QTableWidgetItem(codec->toUnicode("知识水平")));
    table->setItem(4, 0, new QTableWidgetItem(codec->toUnicode("总知识水平")));
    table->setItem(5, 0, new QTableWidgetItem(codec->toUnicode("科研经验")));
    table->setItem(6, 0, new QTableWidgetItem(codec->toUnicode("恋爱天数")));
    table->setItem(7, 0, new QTableWidgetItem(codec->toUnicode("PRP次数")));
    table->setItem(8, 0, new QTableWidgetItem(codec->toUnicode("大创次数")));

    for (int i = 0; i < n; i++) table->setItem(i, 1, new QTableWidgetItem());
}

void MainWindow::setTable(int i, int j, std::string text) {
    table->item(i, j)->setText(text.c_str());
}
void MainWindow::flushTable() {
    attr current = controller->getMainCharacter().getAttributes();
    setTable(0, 1, std::to_string(current[AttributeEnum::term]));
    setTable(1, 1, std::to_string(current[AttributeEnum::physical_quality]));
    setTable(2, 1, std::to_string(current[AttributeEnum::pressure]));
    setTable(3, 1, std::to_string(current[AttributeEnum::knowledge]));
    setTable(4, 1, std::to_string(current[AttributeEnum::all_knowledge]));
    setTable(5, 1, std::to_string(current[AttributeEnum::scientific_research_time]));
    setTable(6, 1, std::to_string(current[AttributeEnum::time_love]));
    setTable(7, 1, std::to_string(current[AttributeEnum::number_prp]));
    setTable(8, 1, std::to_string(current[AttributeEnum::number_novation]));
}

void MainWindow::initButtons() {
    qDebug() << "Init buttons...";

    buttonsLayout = new QVBoxLayout(ui->buttons);
    buttonsLayout->setDirection(QVBoxLayout::TopToBottom);
    for(int i = 0; i < MAX_OPTION_NUM; i++) {
        buttons[i] = new QPushButton("...");
        buttons[i]->setFont(QFont("微软雅黑", 12));
        buttonsLayout->addWidget(buttons[i], 2);
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

    Event* event = controller->getCurrentEvent();

    if (event->type == EventEnum::Baoyan || event->type == EventEnum::Work || event->type == EventEnum::Withdraw) {
        gameEnd(event->type);
        return true;
    }
    //qDebug() << "Changing buttons' status...";

    if (event->type == EventEnum::InnovateProgramDailyEvent) {
        optionNum = event->optionSet.size();
        for (int i = 0; i < 3; i++) {
            buttons[i]->setText(codec->toUnicode(event->optionSet.findOption(i)->second.c_str()));
            buttons[i]->setDisabled(false);
        }
        buttons[3]->setText("");
        buttons[3]->setDisabled(true);
        buttons[4]->setText(codec->toUnicode(event->optionSet.findOption(4)->second.c_str()));
        buttons[4]->setDisabled(false);
        return true;
    }
    optionNum = event->optionSet.size();
    for (int i = 0; i < optionNum; i++) {
        buttons[i]->setText(codec->toUnicode(event->optionSet.findOption(i)->second.c_str()));
        buttons[i]->setDisabled(false);
    }
    for (int i = optionNum; i < MAX_OPTION_NUM; i++) {
        buttons[i]->setText("");
        buttons[i]->setDisabled(true);
    }

    //qDebug() << "Done.";
    return true;
}

bool MainWindow::isGameEnd() {
    return gameEndFlag;
}

void MainWindow::closeEvent(QCloseEvent*) {
    //parentWidget()->show();
}

void MainWindow::on_actionsave_triggered() {
    SaveInfo info = SaveInfo::getCurrentSaveInfo(controller->getMainCharacter(), controller->getCurrentEvent(), getText());
    LoadSave *loadsave = new LoadSave(this, true);
    loadsave->setWindowFlag(Qt::Window);
    loadsave->setAttribute(Qt::WA_DeleteOnClose);
    loadsave->setWindowModality(Qt::ApplicationModal);
    loadsave->setInfo(info);
    loadsave->show();
}
