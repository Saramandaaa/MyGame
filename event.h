// Update at 11/30, 22:50. By 唐梓皓, 添加OptionSet. 

#ifndef EVENT_H
#define EVENT_H

#include <vector>
#include <string>
#include "character.h"
#include "optionset.h"

// 表示所有事件的个数
#define EVENT_AMT (int)EventEnum::Event_End

// 所有事件的枚举，更新时必须手动同步更新 EVENT_AMT
enum class EventEnum
{
    BasicDailyEvent = 0,
    PrpDailyEvent = 1,
    InnovateProgramDailyEvent = 2,

    MidTermExam = 3,
    finalTermExam = 4,
    entranceExam = 5,
    newTerm = 6,

    Prp = 7,
    InnovateProgram = 8,
    JoinCorporation = 9,
    VoteStudentAssociation = 10,

    Love = 11,
    sayGoodBye = 12,

    physicalDisease = 13,
    mentalDisease = 14,

    Withdraw = 15,
    Baoyan = 16,
    Work = 17,

    PrpFinish = 18,
    InnovateFinish = 19,

    TotallyGoodBye = 20,

    Event_End
};

std::string getEventName(int type);

class Event {
public:
    virtual attr getDelta(const Character*, const int) const;
    virtual double getWeight(const Character* character) const;
    std::string getText(void) const;
    void changeText(const std::string&);
    void changeWeight(const double);
    virtual ~Event();
    Event() : weight(1), priority(0) {};
    Event(const std::string& t) : text(t), weight(1), priority(0) {};
    OptionSet optionSet;
    EventEnum type;
    int priority;
    bool comparePriority(Event* first, Event* second) const;
private:
    std::string text;
protected:
    double weight;
};

class TestEvent : public Event {
public:
    attr getDelta(const Character*, const int) const;
};

#endif // EVENT_H
