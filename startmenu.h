#ifndef STARTMENU_H
#define STARTMENU_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class StartMenu; }
QT_END_NAMESPACE

class StartMenu : public QWidget {
    Q_OBJECT

public:
    explicit StartMenu(QWidget *parent = nullptr);
    ~StartMenu();
    void StartGame();
private slots:
    void on_exit_clicked();

    void on_startgame_clicked();

    void on_loadsaves_clicked();

private:
    Ui::StartMenu *ui;
};

#endif // STARTMENU_H
