#include "eventlist.h"
#include "event.h"
#include "eventheader.h"
#include <ctime>

RandSummoner EventList::rs((int)time(NULL));

void EventList::load(SaveInfo info) {
    rs.load(info.seed, info.stepAMT);
}

Event* EventList::getNewEvent(const Character* c) {
    //main function here
    return getDailyEvent(c);
}

Event* EventList::getDailyEvent(const Character *c) {
    DailyEvent *result = new DailyEvent("学期" + std::to_string(c->getSingleAttribute(AttributeEnum::term)) + " 日常事件");
    if (c->getSingleAttribute(AttributeEnum::is_of_prp)) result->addPrp();
    if (c->getSingleAttribute(AttributeEnum::is_of_novation)) result->addNovation();
    return (Event*)result;
}

/*
enum class EventEnum
{
    BasicDailyEvent = 0,
    PrpDailyEvent = 1,
    InnovateProgramDailyEvent = 2,

    MidTermExam = 3,
    finalTermExam = 4,
    entranceExam = 5,

    Prp = 6,
    InnovateProgram = 7,
    JoinCorporation = 8,
    VoteStudentAssociation = 9,

    Love = 10,
    sayGoodBye = 11,

    physicalDisease = 12,
    mentalDisease = 13,

    Withdraw = 14,
    Baoyan = 15,
    Work = 16
};
 */

Event* EventList::getEvent(EventEnum type) {
    void* event;
    switch (type) {
        case EventEnum::BasicDailyEvent:
            event = new DailyEvent("");
        break;

        case EventEnum::PrpDailyEvent:
            event = new DailyEvent("");
            ((DailyEvent*)event)->addPrp();
        break;

        case EventEnum::InnovateProgramDailyEvent:
            event = new DailyEvent("");
            ((DailyEvent*)event)->addNovation();
        break;

        case EventEnum::MidTermExam:
            event = new MidTermExam("");
        break;

        case EventEnum::finalTermExam:
            event = new FinalTermExam("");
        break;

        case EventEnum::entranceExam:
            event = new EntranceExam("");
        break;

        case EventEnum::Prp:
            event = new Prp("");
        break;

        case EventEnum::InnovateProgram:
            event = new InnovateProgram("");
        break;

        case EventEnum::JoinCorporation:
            event = new JoinCorporation("");
        break;

        case EventEnum::VoteStudentAssociation:
            event = new VoteStudentAssociation("");
        break;

        case EventEnum::Love:
            event = new Love("");
        break;

        case EventEnum::sayGoodBye:
            event = new SayGoodBye("");
        break;

        case EventEnum::physicalDisease:
            event = new PhysicalDisease("");
        break;

        case EventEnum::mentalDisease:
            event = new MentalDisease("");
        break;

        case EventEnum::Withdraw:
            event = new Withdraw("");
        break;

        case EventEnum::Baoyan:
            event = new Baoyan("");
        break;

        case EventEnum::Work:
            event = new Work("");
        break;
    }
    return (Event*)event;
}
