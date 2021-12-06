#include "loadsave.h"
#include "ui_loadsave.h"
#include <QDebug>
#include <assert.h>

LoadSave::LoadSave(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::LoadSave)
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
    saves->addItem(new QListWidgetItem("asda"));
    saves->addItem(new QListWidgetItem("asdas"));
    saves->addItem(new QListWidgetItem("asdaasdas"));
    saves->addItem(new QListWidgetItem("asdadsaasdad"));
    saves->addItem(new QListWidgetItem("asdadsaasdasdsad"));
}

void LoadSave::specific_saves_selected() {
    confirm->setDisabled(false);
}

void LoadSave::on_confirm_clicked()
{
    assert (saves->currentItem() != nullptr);
    qDebug() << "Confirm!";
    qDebug() << saves->currentItem()->text();
}

void LoadSave::on_cancel_clicked()
{
    close();
}

void LoadSave::on_flush_clicked()
{
    flush();
    confirm->setDisabled(true);
}

void LoadSave::closeEvent(QCloseEvent *event) {
    parentWidget()->show();
}
