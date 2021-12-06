#ifndef LOADSAVE_H
#define LOADSAVE_H

#include <QWidget>
#include <QPushButton>
#include <QListWidget>
#include <QListWidgetItem>

QT_BEGIN_NAMESPACE
namespace Ui { class LoadSave; }
QT_END_NAMESPACE

class LoadSave : public QWidget {
    Q_OBJECT

public:
    explicit LoadSave(QWidget *parent = nullptr);
    ~LoadSave();
    void closeEvent(QCloseEvent *event);

private slots:
    void specific_saves_selected();

    void on_confirm_clicked();

    void on_cancel_clicked();

    void on_flush_clicked();

private:
    Ui::LoadSave *ui;
    QListWidget *saves;
    QPushButton *confirm;

    void initSaves();
    void flush();
};

#endif // LOADSAVE_H
