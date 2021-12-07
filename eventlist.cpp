#include "eventlist.h"
#include "event.h"
#include "dailyevent.h"
#include <ctime>

int id = 0;

RandSummoner EventList::rs((int)time(NULL));

Event* EventList::getNewEvent(const Character* c) {
    id++;
    DailyEvent *result = new DailyEvent("日常事件");
    if (c->getSingleAttribute(AttributeEnum::is_of_prp)) result->addPrp();
    if (c->getSingleAttribute(AttributeEnum::is_of_novation)) result->addNovation();
    return (Event*)result;
}
