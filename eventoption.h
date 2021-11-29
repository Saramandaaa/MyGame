#ifndef EVENTOPTION_H
#define EVENTOPTION_H

#include <QPushButton>
#include <QApplication>

class EventOption : public QObject {
    Q_OBJECT
signals:
    void choose(int id);
public:
    QPushButton *button;
    int id;
    void emitChoose() {
        emit choose(this->id);
    }
    EventOption(QPushButton *but, int i = 0) : button(but), id(i) {
        QObject::connect(button, &QPushButton::clicked, this, &EventOption::emitChoose);
    };
};

#endif // EVENTOPTION_H
