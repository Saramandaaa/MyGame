#include"controller.h"
#include"event.h"
#include"character.h"
#include"eventlist.h"
#include"mainwindow.h"
#include<qdebug.h>

void Controller::run(const int option, const void* w) {
    attr delta = this->currentEvent->getDelta(this->mainCharacter, option);
    Character* newCharacter = mainCharacter->update(delta);
    Event* newEvent = EventList::getNewEvent(newCharacter);
    delete this->mainCharacter;
    this->mainCharacter = newCharacter;
    delete this->currentEvent;
    this->currentEvent = newEvent;
    ((MainWindow*)w)->flush();
}

Event Controller::getCurrentEvent() {
    return *this->currentEvent;
}
Character Controller::getMainCharacter() {
    return *this->mainCharacter;
}
