#include"eventlist.h"
#include"event.h"

int id = 0;

Event* EventList::getNewEvent(const Character*) {
    Event *event = new TestEvent();
    event->changeText("TestEvent:" + std::to_string(id++));
    event->optionSet.insertOption(0, "+1s");
    event->optionSet.insertOption(1, "+2s");
    if (id & 1) event->optionSet.insertOption(2, "+3s");
    return event;
}
