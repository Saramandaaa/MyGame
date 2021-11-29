#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <string>
#include <vector>
#include <qdebug.h>
#include "controller.h"

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
    void flush();
    void setText(const std::string& text);
    void emitButtonClicked(int option) {
        emit buttonClicked(option, this);
    }

private:
    Ui::MainWindow *ui;
    Controller *controller;
};
#endif // MAINWINDOW_H
