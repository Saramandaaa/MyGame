#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include "event.h"
#include "character.h"

class Controller : public QObject{
    Q_OBJECT
public:
    void run(const int, const void*);
    bool isReady();
    Event getCurrentEvent();
    Character getMainCharacter();
    Controller() {
        currentEvent = new Event();
        mainCharacter = new Character();
    }
private:
    Event* currentEvent;
    Character* mainCharacter;
};

#endif // CONTROLLER_H
