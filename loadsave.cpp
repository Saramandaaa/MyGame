#include "loadsave.h"
#include "ui_loadsave.h"
#include "textcode.h"
#include <QDebug>
#include <assert.h>
#include "saveinfo.h"
#include "startmenu.h"
#include <QMessageBox>

LoadSave::LoadSave(QWidget *parent, bool is_save_mode)
    : QWidget(parent)
    , ui(new Ui::LoadSave), save_mode(is_save_mode)
{
    ui->setupUi(this);
    saves = ui->saves;
    confirm = (QPushButton*)ui->horizontalLayout->itemAt(1)->widget();
    confirm->setDisabled(true);
    initSaves();
    flush();
}

LoadSave::~LoadSave() {
    delete ui;
}

void LoadSave::initSaves() {
    saves->setFont(QFont("΢���ź�", 9));
    QObject::connect(saves, &QListWidget::itemClicked, this, &LoadSave::specific_saves_selected);
}

void LoadSave::flush() {
    saves->clear();
    if (save_mode) saves->addItem(new QListWidgetItem(codec->toUnicode("�´浵")));
    FileList Flist;
    for (int i = 0; i < (int)Flist.vectorlist.size(); i++) {
        std::string readname = "�浵ʱ��: " + Flist.readable(Flist.vectorlist[i]);
        saves->addItem(new QListWidgetItem(codec->toUnicode(readname.c_str())));
    }
    confirm->setDisabled(true);
}

void LoadSave::specific_saves_selected() {
    confirm->setDisabled(false);
}

void LoadSave::on_confirm_clicked() //���ȷ�Ϻ�
{
    assert (saves->currentItem() != nullptr);
    //qDebug() << "Confirm!";
    //qDebug() << saves->currentItem()->text();
    int id = saves->currentRow();
    FileList Flist;
    if (save_mode) {
        if (id == 0) { //�´浵
            if (Flist.save_to_new(info)) {
                flush();
            }
            else {
                //save new error
            }
        }
        else { //���Ǿɴ浵
            QMessageBox::StandardButton result = QMessageBox::question(this, codec->toUnicode("��ʾ"), codec->toUnicode("�����Ǵ浵��ȷ�ϼ�����"));
            if (result == QMessageBox::Yes) {
                if (Flist.save_to(info, Flist.vectorlist[id - 1])) {
                    flush();
                }
                else {
                    //save error
                }
            }
        }
    }
    else { //��ȡ�浵
        if (Flist.load_from(info, Flist.vectorlist[id])) {
            emit_save_info_loaded();
            close();
        }
        else {
            //load error
        }
    }
}

void LoadSave::setInfo(SaveInfo in) {
    info = in;
}

SaveInfo LoadSave::getInfo() {
    return info;
}

void LoadSave::on_cancel_clicked() {
    close();
}

void LoadSave::on_flush_clicked() {
    flush();
}

void LoadSave::closeEvent(QCloseEvent*) {
    //parentWidget()->show();
}
