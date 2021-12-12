#ifndef LOADSAVE_H
#define LOADSAVE_H

#include <QWidget>
#include <QPushButton>
#include <QListWidget>
#include <QListWidgetItem>

#include "Headers/utility/saveinfo.h"

QT_BEGIN_NAMESPACE
namespace Ui { class LoadSave; }
QT_END_NAMESPACE

class LoadSave : public QWidget {
    Q_OBJECT

signals:
    void save_info_loaded(SaveInfo);

public:
    explicit LoadSave(QWidget *parent = nullptr, bool is_save_mode = false);
    ~LoadSave();
    void closeEvent(QCloseEvent *event);
    void setInfo(SaveInfo);
    SaveInfo getInfo();
    void emit_save_info_loaded() {
        emit save_info_loaded(info);
    }

private slots:
    void specific_saves_selected();

    void on_confirm_clicked();

    void on_cancel_clicked();

    void on_flush_clicked();

private:
    Ui::LoadSave *ui;
    QListWidget *saves;
    QPushButton *confirm;
    bool save_mode;
    SaveInfo info;

    void initSaves();
    void flush();
};

#endif // LOADSAVE_H
