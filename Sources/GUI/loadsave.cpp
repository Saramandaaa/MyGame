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
    saves->setFont(QFont("Î¢ÈíÑÅºÚ", 9));
    QObject::connect(saves, &QListWidget::itemClicked, this, &LoadSave::specific_saves_selected);
}

void LoadSave::flush() {
    saves->clear();
    if (save_mode) saves->addItem(new QListWidgetItem(codec->toUnicode("ÐÂ´æµµ")));
    FileList Flist;
    for (int i = 0; i < (int)Flist.vectorlist.size(); i++) {
        std::string readname = "´æµµÊ±¼ä: " + Flist.readable(Flist.vectorlist[i]);
        saves->addItem(new QListWidgetItem(codec->toUnicode(readname.c_str())));
    }
    confirm->setDisabled(true);
}

void LoadSave::specific_saves_selected() {
    confirm->setDisabled(false);
}

void LoadSave::on_confirm_clicked() //µã»÷È·ÈÏºó
{
    assert (saves->currentItem() != nullptr);
    //qDebug() << "Confirm!";
    //qDebug() << saves->currentItem()->text();
    int id = saves->currentRow();
    FileList Flist;
    if (save_mode) {
        if (id == 0) { //ÐÂ´æµµ
            if (Flist.save_to_new(info)) {
                flush();
            }
            else {
                //save new error
            }
        }
        else { //¸²¸Ç¾É´æµµ
            QMessageBox::StandardButton result = QMessageBox::question(this, codec->toUnicode("ÌáÊ¾"), codec->toUnicode("½«¸²¸Ç´æµµ£¬È·ÈÏ¼ÌÐø£¿"));
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
    else { //¶ÁÈ¡´æµµ
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
