#include"controller.h"
#include"event.h"
#include"character.h"
#include"eventlist.h"
#include"mainwindow.h"
#include<qdebug.h>

Controller::Controller() {
    currentEvent = nullptr;
    mainCharacter = nullptr;
}

void Controller::init() {
    mainCharacter = new Character();
    currentEvent = EventList::getNewEvent(mainCharacter);
}

void Controller::run(const int option, const void* w) {
    if (!isReady()) return;
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

bool Controller::isReady() {
    return currentEvent != nullptr && mainCharacter != nullptr;
}
