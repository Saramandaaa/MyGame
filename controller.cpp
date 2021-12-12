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
    currentEvent->optionSet.clearOption();
    currentEvent->optionSet.insertOption(0, "开始");
}

void Controller::run(const int option, const void* w) {
    if (!isReady() || ((MainWindow*)w)->isGameEnd()) return;
    ((MainWindow*)w)->setText("选择了:");
    ((MainWindow*)w)->setText(currentEvent->optionSet.findOption(option)->second + "\n");
    std::string message;
    attr delta = this->currentEvent->getDelta(this->mainCharacter, option, message);
    qDebug() << message.c_str();
    if ((int)message.size() > 0) {
        ((MainWindow*)w)->setText(message + "\n");
    }
    ((MainWindow*)w)->setText("\n");

    mainCharacter = mainCharacter->update(delta);

    Event* newEvent = EventList::getNewEvent(mainCharacter);
    delete this->currentEvent;
    this->currentEvent = newEvent;

    ((MainWindow*)w)->flush();
}

Event* Controller::getCurrentEvent() {
    return this->currentEvent;
}
Character Controller::getMainCharacter() {
    return *this->mainCharacter;
}

bool Controller::isReady() {
    return currentEvent != nullptr && mainCharacter != nullptr;
}

void Controller::setMainCharacter(Attribute c) {
    delete mainCharacter;
    mainCharacter = new Character(c);
}

void Controller::setCurrentEvent(Event *event) {
    currentEvent = event;
}
