#include"eventlist.h"
#include"event.h"

int id = 0;

Event* EventList::getNewEvent(const Character*) {
    Event *event = new TestEvent();
    event->changeText("TestEvent:��������");
    event->optionSet.insertOption(0, "+1����");
    event->optionSet.insertOption(1, "+2����");
    if (id & 1) event->optionSet.insertOption(2, "+3����");
    return event;
}
