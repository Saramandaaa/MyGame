#ifndef STARTMENU_H
#define STARTMENU_H

#include <QWidget>

#include "Headers/utility/saveinfo.h"

QT_BEGIN_NAMESPACE
namespace Ui { class StartMenu; }
QT_END_NAMESPACE

class StartMenu : public QWidget {
    Q_OBJECT

public:
    explicit StartMenu(QWidget *parent = nullptr);
    ~StartMenu();
    void startGame(bool from_save = false);
    void setInfo(SaveInfo);
    SaveInfo getInfo();

private slots:
    void on_exit_clicked();

    void on_startgame_clicked();

    void on_loadsaves_clicked();

    void continue_from_save(SaveInfo);

private:
    Ui::StartMenu *ui;
    SaveInfo info;
};

#endif // STARTMENU_H
