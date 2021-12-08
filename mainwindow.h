#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLayout>
#include <string>
#include <vector>
#include <QDebug>
#include "controller.h"
#include "event.h"
#include "saveinfo.h"
#include <QTextCodec>
#include <QVBoxLayout>
#include <QPointer>
#include <QDebug>
#include <QTableWidget>
#include <QTableWidgetItem>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

signals:
    void buttonClicked(int option, void* w);
public:
    MainWindow(QWidget *parent = nullptr);
    MainWindow(SaveInfo info, QWidget *parent = nullptr);
    ~MainWindow();
    void flush(); //更新事件显示
    void setText(const std::string& text); //设置事件描述
    std::string getText();

    void emitButtonClicked0() {
        setText("选择了选项:");
        emit buttonClicked(0, this);
    }
    void emitButtonClicked1() {
        setText("选择了选项:");
        emit buttonClicked(1, this);
    }
    void emitButtonClicked2() {
        setText("选择了选项:");
        emit buttonClicked(2, this);
    }
    void emitButtonClicked3() {
        setText("选择了选项:");
        emit buttonClicked(3, this);
    }
    void emitButtonClicked4() {
        setText("选择了选项:");
        emit buttonClicked(4, this);
    }
    void closeEvent(QCloseEvent *event);

private slots:
    void on_actionsave_triggered();

private:
    Ui::MainWindow *ui;
    Controller *controller;
    QPushButton *buttons[MAX_OPTION_NUM];
    int optionNum;
    QVBoxLayout *buttonsLayout;
    QTableWidget *table;

    void initFromSaveInfo(SaveInfo);
    void initAttrTable();
    void updateAttr();
    void initController();
    void initMenuBar();
    void initButtons(); //连接到按钮
    bool loadCurrentEvent(); //读取当前事件
    void setTable(int, int, std::string);
    void flushTable();

};
#endif // MAINWINDOW_H
