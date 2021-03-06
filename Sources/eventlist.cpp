#include <ctime>

#include "Headers/eventHeap.h"
#include "Headers/eventlist.h"
#include "Headers/basicheader.h"
#include "Events/eventheader.h"

RandSummoner EventList::rs((int)time(NULL));
EventHeap EventList::eventHeap;
int EventList::preEvent;

void EventList::load(SaveInfo info) {
    rs.load(info.seed, info.stepAMT);
}

Event* EventList::getNewEvent(const Character* c) {
    //main function here
    double* weights = new double[EVENT_AMT];
    double total = getAllWeights(c, weights);

    if (eventHeap.length) return eventHeap.pop();

    double random = rs.step() * total;
    int eventType = 0;

    for (; eventType < EVENT_AMT && random >= weights[eventType]; eventType++) {
        random -= weights[eventType];
    }

    Event* result;
    if (eventType == (int)EventEnum::BasicDailyEvent
     || eventType == (int)EventEnum::PrpDailyEvent
     || eventType == (int)EventEnum::InnovateProgramDailyEvent)
        result = getDailyEvent(c);
    else result = getEvent((EventEnum)eventType);

    delete[] weights;
    return result;
}

double EventList::getAllWeights(const Character* character, double* weights) {
    Event* temp;
    double tempWeight;
    double total = 0;
    for (int i = 0; i < EVENT_AMT; i++) {
        temp = getEvent((EventEnum)i);
        tempWeight = temp->getWeight(character);
        if (tempWeight < -0.5) {
            weights[i] = 0;
            eventHeap.insert(temp);
        }
        else weights[i] = tempWeight;
        total += weights[i];
    }
    return total;
}

Event* EventList::getDailyEvent(const Character *c) {
    DailyEvent *result = new DailyEvent("每天的日常...");
    if (c->getSingleAttribute(AttributeEnum::is_of_prp)) result->addPrp();
    if (c->getSingleAttribute(AttributeEnum::is_of_novation)) result->addNovation();
    if (c->getSingleAttribute(AttributeEnum::is_mental_ill) || c->getSingleAttribute(AttributeEnum::is_physical_ill))
        result->ill(c);
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
            event = new DailyEvent();
        break;

        case EventEnum::PrpDailyEvent:
            event = new DailyEvent();
            ((DailyEvent*)event)->addPrp();
        break;

        case EventEnum::InnovateProgramDailyEvent:
            event = new DailyEvent();
            ((DailyEvent*)event)->addNovation();
        break;

        case EventEnum::MidTermExam:
            event = new MidTermExam();
        break;

        case EventEnum::finalTermExam:
            event = new FinalTermExam();
        break;

        case EventEnum::entranceExam:
            event = new EntranceExam();
        break;

        case EventEnum::newTerm:
            event = new NewTerm();
        break;

        case EventEnum::Prp:
            event = new Prp();
        break;

        case EventEnum::InnovateProgram:
            event = new InnovateProgram();
        break;

        case EventEnum::JoinCorporation:
            event = new JoinCorporation();
        break;

        case EventEnum::VoteStudentAssociation:
            event = new VoteStudentAssociation();
        break;

        case EventEnum::Love:
            event = new Love();
        break;

        case EventEnum::sayGoodBye:
            event = new SayGoodBye();
        break;

        case EventEnum::physicalDisease:
            event = new PhysicalDisease();
        break;

        case EventEnum::mentalDisease:
            event = new MentalDisease();
        break;

        case EventEnum::Withdraw:
            event = new Withdraw();
        break;

        case EventEnum::Baoyan:
            event = new Baoyan();
        break;

        case EventEnum::Work:
            event = new Work();
        break;
        case EventEnum::InnovateFinish:
            event = new InnovateFinish();
        break;
        case EventEnum::PrpFinish:
            event = new PrpFinish();
        break;
        case EventEnum::TotallyGoodBye:
            event = new TotallyGoodBye();
        break;
        default:
            event = nullptr;
    }
    return (Event*)event;
}
