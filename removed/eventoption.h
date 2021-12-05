#ifndef EVENTOPTION_H
#define EVENTOPTION_H

#include <QPushButton>
#include <QApplication>
#include <QDebug>

class EventOption : public QObject {
    Q_OBJECT
signals:
    void choose(int id);
public:
    QPushButton *button;
    int id;
    QMetaObject::Connection connect;
    void emitChoose() {
        qDebug() << "asdaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
        emit choose(this->id);
    }
    void setConnection() {
        connect = QObject::connect(button, &QPushButton::clicked, this, &EventOption::emitChoose);
    }
    void removeConnection() {
        QObject::disconnect(connect);
    }
    EventOption() {}
    EventOption(QPushButton *but, int i = 0) : button(but), id(i) {}
};

#endif // EVENTOPTION_H
