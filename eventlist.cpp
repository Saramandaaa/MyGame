#include"eventlist.h"
#include"event.h"

int id = 0;

Event* EventList::getNewEvent(const Character*) {
    return new Event(std::to_string(id++));
}
