#ifndef EVENTLIST_H
#define EVENTLIST_H

#include "character.h"
#include "event.h"
#include "saveinfo.h"
#include "randsummoner.h"

class EventList {
public:
    static Event* getNewEvent(const Character*);
    static RandSummoner rs;
    static void load(SaveInfo);
    static Event* getLastEvent();
private:

};

#endif // EVENTLIST_H
