#ifndef EVENTLIST_H
#define EVENTLIST_H

#include "Headers/basicheader.h"
#include "Headers/eventHeap.h"
#include "Headers/utility/saveinfo.h"
#include "Headers/utility/randsummoner.h"

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
