#include "attribute.h"
#include "character.h"
#include "event.h"
#include <string>
#include <assert.h>

class DailyEvent : public Event {
public:
    //构造函数，需要提供事件描述，在eventlist中用于创建事件实体
    DailyEvent();
    DailyEvent(const std::string t);
    //c为角色，o为选择的选项，从0开始编号
    //对于日常事件，0学习，1运动，2娱乐，3prp，4大创
    attr getDelta(const Character* c, const int o) const;
    double getWeight(const Character* character) const;

    //创建实体时可能需要添加相应选项
    void addPrp();
    void addNovation();

private:
    //修改最近的5次事件
    attr change_affairs(const Character* c, const int o, attr delta) const;

    //各个选择的
    attr daily_event_study(const Character* c) const;
    attr daily_event_exercise(const Character* c) const;
    attr daily_event_entertainment(const Character* c) const;
    attr daily_event_prp(const Character* c) const;
    attr daily_event_novation(const Character* c) const;
};

DailyEvent::DailyEvent() :
    DailyEvent("日常")
{

}

DailyEvent::DailyEvent(const std::string t) {
    type = EventEnum::BasicDailyEvent;
    changeText(t);
    changeWeight(10);
    optionSet.insertOption(0, "学习");
    optionSet.insertOption(1, "运动");
    optionSet.insertOption(2, "娱乐");
}
void DailyEvent::addPrp() {
    type = EventEnum::PrpDailyEvent;
    optionSet.insertOption(3, "进行PRP活动");
}
void DailyEvent::addNovation() {
    type = EventEnum::InnovateProgramDailyEvent;
    optionSet.insertOption(4, "进行大创活动");
}

attr DailyEvent::getDelta(const Character* c, const int o) const {
    attr result;

    if (o == 0) result = daily_event_study(c);
    else if (o == 1) result = daily_event_exercise(c);
    else if (o == 2) result = daily_event_entertainment(c);
    else if (o == 3) result = daily_event_prp(c);
    else if (o == 4) result = daily_event_novation(c);
    else assert(false);
    result[AttributeEnum::day] = 1;
    if (c->getSingleAttribute(AttributeEnum::is_of_love)) result[AttributeEnum::time_love] = 1;
    if (c->getSingleAttribute(AttributeEnum::goodByeDay)) result[AttributeEnum::goodByeDay] = -1;
    if (c->getSingleAttribute(AttributeEnum::randomEventCoolDown)) result[AttributeEnum::randomEventCoolDown] = -1;
    //修改最近的事件
    return change_affairs(c, o, result);
}

double DailyEvent::getWeight(const Character* character) const {
    switch (type) {
    case EventEnum::BasicDailyEvent:
        if (character->getSingleAttribute(AttributeEnum::is_of_prp)) return 0;
        if (character->getSingleAttribute(AttributeEnum::is_of_novation)) return 0;
        break;
    case EventEnum::PrpDailyEvent:
        if (!character->getSingleAttribute(AttributeEnum::is_of_prp)) return 0;
        break;
    case EventEnum::InnovateProgramDailyEvent:
        if (!character->getSingleAttribute(AttributeEnum::is_of_novation)) return 0;
        break;
    default:
        assert(false);
        break;
    }
    return weight * 1;
}

attr DailyEvent::change_affairs(const Character* c, const int o, attr delta) const {
    delta[AttributeEnum::affair0] = o;
    delta[AttributeEnum::affair1] = c->getSingleAttribute(AttributeEnum::affair0);
    delta[AttributeEnum::affair2] = c->getSingleAttribute(AttributeEnum::affair1);
    delta[AttributeEnum::affair3] = c->getSingleAttribute(AttributeEnum::affair2);
    delta[AttributeEnum::affair4] = c->getSingleAttribute(AttributeEnum::affair3);
    return delta;
}

//每学期知识水平delta=（（学习效率+（身体素质-0.7）-（心里压力-0.4））>0)*0.13;
//学习效率delta=-0.15；
//身体素质delta=-(近5次事件中学习、task事件次数*1.5-运动事件次数*2+娱乐事件次数)*0.03;
//心里压力delta=(近5次事件中学习、task事件次数*2-运动事件次数*2-娱乐事件次数*4)*0.05;
//注意可读性,实际数值为0-100,需要整体扩大100倍
attr DailyEvent::daily_event_study(const Character* c) const {
    attr delta;

    ATTR_TYPE study_rate       = c->getSingleAttribute(AttributeEnum::study_rate);
    ATTR_TYPE physical_quality = c->getSingleAttribute(AttributeEnum::physical_quality);
    ATTR_TYPE pressure         = c->getSingleAttribute(AttributeEnum::pressure);

    //获取近5次事件统计
    int count_study         = c->getAttributes().getStudy() + c->getAttributes().getTask();
    int count_exercise      = c->getAttributes().getExercise();
    int count_entertainment = c->getAttributes().getEntertainment();

    double delta_knowledge = (study_rate +(physical_quality - 70) - (pressure - 40));
    if (delta_knowledge > 0) delta_knowledge *= 0.13;
    else delta_knowledge = 0;

    double delta_study_rate = -15;

    double delta_physical_quality = -(count_study * 1.5 - count_exercise * 2 + count_entertainment) * 3;

    double delta_pressure = (count_study * 2 - count_exercise * 2 - count_entertainment * 4) * 5;

    delta[AttributeEnum::knowledge]        = (ATTR_TYPE)delta_knowledge;
    delta[AttributeEnum::study_rate]       = (ATTR_TYPE)delta_study_rate;
    delta[AttributeEnum::physical_quality] = (ATTR_TYPE)delta_physical_quality;
    delta[AttributeEnum::pressure]         = (ATTR_TYPE)delta_pressure;

    return delta;
}

//学习效率delta=0.3-(近5次事件中运动事件次数-1)*0.15;
//身体素质delta=0.2;
//心里压力delta=-0.15;
//社交能力delta=0.5;
attr DailyEvent::daily_event_exercise(const Character *c) const {
    attr delta;

    //ATTR_TYPE study_rate       = c->getSingleAttribute(AttributeEnum::study_rate);
    //ATTR_TYPE physical_quality = c->getSingleAttribute(AttributeEnum::physical_quality);
    //ATTR_TYPE pressure         = c->getSingleAttribute(AttributeEnum::pressure);

    //获取近5次事件统计
    //int count_study         = c->getAttributes().getStudy() + c->getAttributes().getTask();
    int count_exercise      = c->getAttributes().getExercise();
    //int count_entertainment = c->getAttributes().getEntertainment();

    double delta_study_rate = 30 - (count_exercise - 1) * 15;

    double delta_physical_quality = 20;

    double delta_pressure = -15;

    double delta_social = 50;

    delta[AttributeEnum::study_rate]       = (ATTR_TYPE)delta_study_rate;
    delta[AttributeEnum::physical_quality] = (ATTR_TYPE)delta_physical_quality;
    delta[AttributeEnum::pressure]         = (ATTR_TYPE)delta_pressure;
    delta[AttributeEnum::social]           = (ATTR_TYPE)delta_social;

    return delta;
}

//学习效率delta=0.45-（近5次事件中娱乐事件次数-1)*0.25;
//身体素质delta=-0.05；
//心里压力delta=-0.2;
//社交能力delta=1;
attr DailyEvent::daily_event_entertainment(const Character *c) const {
    attr delta;

    //ATTR_TYPE study_rate       = c->getSingleAttribute(AttributeEnum::study_rate);
    //ATTR_TYPE physical_quality = c->getSingleAttribute(AttributeEnum::physical_quality);
    //ATTR_TYPE pressure         = c->getSingleAttribute(AttributeEnum::pressure);

    //获取近5次事件统计
    //int count_study         = c->getAttributes().getStudy() + c->getAttributes().getTask();
    //int count_exercise      = c->getAttributes().getExercise();
    int count_entertainment = c->getAttributes().getEntertainment();

    double delta_study_rate = 45 - (count_entertainment - 1) * 25;

    double delta_physical_quality = -5;

    double delta_pressure = -20;

    double delta_social = 100;

    delta[AttributeEnum::study_rate]       = (ATTR_TYPE)delta_study_rate;
    delta[AttributeEnum::physical_quality] = (ATTR_TYPE)delta_physical_quality;
    delta[AttributeEnum::pressure]         = (ATTR_TYPE)delta_pressure;
    delta[AttributeEnum::social]           = (ATTR_TYPE)delta_social;

    return delta;
}


//每学期知识水平delta=（（学习效率+（身体素质-0.7）-（心里压力-0.4））>0)*0.09;
//学习效率delta=-0.15;
//身体素质delta=-(近5次事件中学习、task事件次数*1.5-运动事件次数*2+娱乐事件次数)*0.03;
//心里压力delta=(近5次事件中学习、task事件次数*2-运动事件次数*2+娱乐事件次数*4)*0.05;
attr DailyEvent::daily_event_prp(const Character *c) const {
    attr delta;

    ATTR_TYPE study_rate       = c->getSingleAttribute(AttributeEnum::study_rate);
    ATTR_TYPE physical_quality = c->getSingleAttribute(AttributeEnum::physical_quality);
    ATTR_TYPE pressure         = c->getSingleAttribute(AttributeEnum::pressure);

    //获取近5次事件统计
    int count_study         = c->getAttributes().getStudy() + c->getAttributes().getTask();
    int count_exercise      = c->getAttributes().getExercise();
    int count_entertainment = c->getAttributes().getEntertainment();

    double delta_knowledge = (study_rate +(physical_quality - 70) - (pressure - 40));
    if (delta_knowledge > 0) delta_knowledge *= 0.09;
    else delta_knowledge = 0;

    double delta_study_rate = -15;

    double delta_physical_quality = -(count_study * 1.5 - count_exercise * 2 + count_entertainment) * 3;

    double delta_pressure = (count_study * 2 - count_exercise * 2 - count_entertainment * 4) * 5;

    delta[AttributeEnum::knowledge]        = (ATTR_TYPE)delta_knowledge;
    delta[AttributeEnum::study_rate]       = (ATTR_TYPE)delta_study_rate;
    delta[AttributeEnum::physical_quality] = (ATTR_TYPE)delta_physical_quality;
    delta[AttributeEnum::pressure]         = (ATTR_TYPE)delta_pressure;
    delta[AttributeEnum::number_prp]       = (ATTR_TYPE)1;

    return delta;
}
attr DailyEvent::daily_event_novation(const Character *c) const {
    attr delta;

    ATTR_TYPE study_rate       = c->getSingleAttribute(AttributeEnum::study_rate);
    ATTR_TYPE physical_quality = c->getSingleAttribute(AttributeEnum::physical_quality);
    ATTR_TYPE pressure         = c->getSingleAttribute(AttributeEnum::pressure);

    //获取近5次事件统计
    int count_study         = c->getAttributes().getStudy() + c->getAttributes().getTask();
    int count_exercise      = c->getAttributes().getExercise();
    int count_entertainment = c->getAttributes().getEntertainment();

    double delta_knowledge = (study_rate +(physical_quality - 70) - (pressure - 40));
    if (delta_knowledge > 0) delta_knowledge *= 0.09;
    else delta_knowledge = 0;

    double delta_study_rate = -15;

    double delta_physical_quality = -(count_study * 1.5 - count_exercise * 2 + count_entertainment) * 3;

    double delta_pressure = (count_study * 2 - count_exercise * 2 - count_entertainment * 4) * 5;

    delta[AttributeEnum::knowledge]        = (ATTR_TYPE)delta_knowledge;
    delta[AttributeEnum::study_rate]       = (ATTR_TYPE)delta_study_rate;
    delta[AttributeEnum::physical_quality] = (ATTR_TYPE)delta_physical_quality;
    delta[AttributeEnum::pressure]         = (ATTR_TYPE)delta_pressure;
    delta[AttributeEnum::number_novation]       = (ATTR_TYPE)1;

    return delta;
}
