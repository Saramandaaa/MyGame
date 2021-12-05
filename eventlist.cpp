#include"eventlist.h"
#include"event.h"

int id = 0;

Event* EventList::getNewEvent(const Character*) {
    Event *event = new TestEvent();
    event->changeText("TestEvent:体质增加");
    event->optionSet.insertOption(0, "+1体质");
    event->optionSet.insertOption(1, "+2体质");
    if (id & 1) event->optionSet.insertOption(2, "+3体质");
    return event;
}
