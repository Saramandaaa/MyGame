#ifndef EVENTLIST_H
#define EVENTLIST_H

#include "eventHeap.h"
#include "character.h"
#include "event.h"
#include "saveinfo.h"
#include "randsummoner.h"

class EventList {
public:
    static Event* getNewEvent(const Character*);
    static RandSummoner rs;
    static EventHeap eventHeap;
    static int preEvent;
    static void load(SaveInfo);
    static Event* getEvent(EventEnum);
    static double getAllWeights(const Character* character, double* weights);
private:
    static Event* getDailyEvent(const Character*);
};

#endif // EVENTLIST_H
