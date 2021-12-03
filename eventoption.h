#ifndef EVENTOPTION_H
#define EVENTOPTION_H

#include <QPushButton>
#include <QApplication>
#include <QPointer>

class EventOption : public QObject {
    Q_OBJECT
signals:
    void choose(int id);
public:
    QPointer<QPushButton> button;
    int id;
    QMetaObject::Connection connect;
    void emitChoose() {
        emit choose(this->id);
    }
    void setConnection() {
        connect = QObject::connect(button, &QPushButton::clicked, this, &EventOption::emitChoose);
    }
    void removeConnection() {
        disconnect(connect);
    }
    EventOption() {}
    EventOption(QPointer<QPushButton> but, int i = 0) : button(but), id(i) {}
};

#endif // EVENTOPTION_H
