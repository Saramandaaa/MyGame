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
    ~MainWindow();
    void flush(); //�����¼���ʾ
    void setText(const std::string& text); //�����¼�����

    void emitButtonClicked0() {
        setText("ѡ����ѡ��:");
        emit buttonClicked(0, this);
    }
    void emitButtonClicked1() {
        setText("ѡ����ѡ��:");
        emit buttonClicked(1, this);
    }
    void emitButtonClicked2() {
        setText("ѡ����ѡ��:");
        emit buttonClicked(2, this);
    }
    void emitButtonClicked3() {
        setText("ѡ����ѡ��:");
        emit buttonClicked(3, this);
    }
    void emitButtonClicked4() {
        setText("ѡ����ѡ��:");
        emit buttonClicked(4, this);
    }

private:
    Ui::MainWindow *ui;
    Controller *controller;
    QPushButton *buttons[MAX_OPTION_NUM];
    int optionNum;
    QVBoxLayout *buttonsLayout;
    QTableWidget *table;

    void initAttrTable();
    void updateAttr();
    void initController();
    void initButtons(); //���ӵ���ť
    bool loadCurrentEvent(); //��ȡ��ǰ�¼�
};
#endif // MAINWINDOW_H
