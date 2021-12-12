#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include "Headers/basicheader.h"

class Controller : public QObject{
    Q_OBJECT
public:
    void run(const int, const void*);
    void init();
    bool isReady();
    Event* getCurrentEvent();
    Character getMainCharacter();
    void setMainCharacter(Attribute);
    void setCurrentEvent(Event*);
    Controller();
private:
    Event* currentEvent;
    Character* mainCharacter;
};

#endif // CONTROLLER_H
