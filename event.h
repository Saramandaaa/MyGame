// Update at 11/30, 22:50. By ÌÆè÷ð©, Ìí¼ÓOptionSet. 

#ifndef EVENT_H
#define EVENT_H

#include <vector>
#include <string>
#include "character.h"
#include "optionset.h"

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


class Event {
public:
    virtual attr getDelta(const Character*, const int) const;
    std::string getText(void) const;
    void changeText(const std::string&);
    virtual ~Event();
    Event() {};
    Event(const std::string& t) : text(t) {};
    OptionSet optionSet;
    EventEnum type;
private:
    std::string text;
};

class TestEvent : public Event {
public:
    attr getDelta(const Character*, const int) const;
};

#endif // EVENT_H
