#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <string>
#include <vector>
#include <qdebug.h>
#include "controller.h"
#include "event.h"
#include "eventoption.h"

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
    ~MainWindow();
    void flush(); //更新事件显示

    void emitButtonClicked(int option) {
        emit buttonClicked(option, this);
    }

private:
    Ui::MainWindow *ui;
    Controller *controller;
    EventOption *options;
    int optionNum;

    void initController();
    void setText(const std::string& text); //设置事件描述
    bool linkButtons(); //连接到按钮
    bool loadCurrentEvent(); //读取当前事件
};
#endif // MAINWINDOW_H
