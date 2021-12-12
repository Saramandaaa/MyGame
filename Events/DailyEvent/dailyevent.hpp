#include <string>
#include <assert.h>

#include "Headers/basicheader.h"

class DailyEvent : public Event {
public:
    //���캯������Ҫ�ṩ�¼���������eventlist�����ڴ����¼�ʵ��
    DailyEvent();
    DailyEvent(const std::string t);
    //cΪ��ɫ��oΪѡ���ѡ���0��ʼ���
    //�����ճ��¼���0ѧϰ��1�˶���2���֣�3prp��4��
    attr getDelta(const Character* c, const int o, std::string&) const;
    double getWeight(const Character* character) const;

    //����ʵ��ʱ������Ҫ�����Ӧѡ��
    void addPrp();
    void addNovation();
    void ill(const Character*);

private:

    bool is_ill;
    //�޸������5���¼�
    attr change_affairs(const Character* c, const int o, attr delta) const;

    //����ѡ���
    attr daily_event_study(const Character* c) const;
    attr daily_event_exercise(const Character* c) const;
    attr daily_event_entertainment(const Character* c) const;
    attr daily_event_prp(const Character* c) const;
    attr daily_event_novation(const Character* c) const;
    attr daily_event_ill(const Character* c) const;
};

DailyEvent::DailyEvent() :
    DailyEvent("ÿ����ճ�...")
{

}

DailyEvent::DailyEvent(const std::string t) : is_ill(false) {
    type = EventEnum::BasicDailyEvent;
    changeText(t);
    changeWeight(10);
    optionSet.insertOption(0, "ѧϰ");
    optionSet.insertOption(1, "�˶�");
    optionSet.insertOption(2, "����");
}
void DailyEvent::addPrp() {
    type = EventEnum::PrpDailyEvent;
    optionSet.insertOption(3, "����PRP�");
}
void DailyEvent::addNovation() {
    type = EventEnum::InnovateProgramDailyEvent;
    optionSet.insertOption(4, "���д󴴻");
}
void DailyEvent::ill(const Character* c) {
    if (c->getSingleAttribute(AttributeEnum::is_physical_ill))
        changeText("��Ϊ���弲������Ҫ�������޷����������ճ����");
    else if (c->getSingleAttribute(AttributeEnum::is_mental_ill))
        changeText("��Ϊ����������Ҫ�������޷����������ճ����");
    else assert(false);
    optionSet.clearOption();
    optionSet.insertOption(0, "����");
    is_ill = true;
}

attr DailyEvent::getDelta(const Character* c, const int o, std::string&) const {
    attr result;

    if (is_ill) {
        assert(o == 0);
        result = daily_event_ill(c);
    }
    else {
        if (o == 0) result = daily_event_study(c);
        else if (o == 1) result = daily_event_exercise(c);
        else if (o == 2) result = daily_event_entertainment(c);
        else if (o == 3) result = daily_event_prp(c);
        else if (o == 4) result = daily_event_novation(c);
        else assert(false);
    }
    result[AttributeEnum::day] = 1;
    if (c->getSingleAttribute(AttributeEnum::is_of_love)) result[AttributeEnum::time_love] = 1;
    if (c->getSingleAttribute(AttributeEnum::goodByeDay)) result[AttributeEnum::goodByeDay] = -1;
    if (c->getSingleAttribute(AttributeEnum::randomEventCoolDown)) result[AttributeEnum::randomEventCoolDown] = -1;
    //�޸�������¼�
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
    if (is_ill) {
        delta[AttributeEnum::affair0] = -1 - c->getSingleAttribute(AttributeEnum::affair0);
        delta[AttributeEnum::affair1] = -1 - c->getSingleAttribute(AttributeEnum::affair1);
        delta[AttributeEnum::affair2] = -1 - c->getSingleAttribute(AttributeEnum::affair2);
        delta[AttributeEnum::affair3] = -1 - c->getSingleAttribute(AttributeEnum::affair3);
        delta[AttributeEnum::affair4] = -1 - c->getSingleAttribute(AttributeEnum::affair4);
    }
    else {
        delta[AttributeEnum::affair0] = o - c->getSingleAttribute(AttributeEnum::affair0);
        delta[AttributeEnum::affair1] = c->getSingleAttribute(AttributeEnum::affair0) - c->getSingleAttribute(AttributeEnum::affair1);
        delta[AttributeEnum::affair2] = c->getSingleAttribute(AttributeEnum::affair1) - c->getSingleAttribute(AttributeEnum::affair2);
        delta[AttributeEnum::affair3] = c->getSingleAttribute(AttributeEnum::affair2) - c->getSingleAttribute(AttributeEnum::affair3);
        delta[AttributeEnum::affair4] = c->getSingleAttribute(AttributeEnum::affair3) - c->getSingleAttribute(AttributeEnum::affair4);
    }
    return delta;
}

attr DailyEvent::daily_event_ill(const Character* c) const {
    attr delta;
    if (c->getSingleAttribute(AttributeEnum::is_mental_ill))
        delta[AttributeEnum::pressure] =
                c->getSingleAttribute(AttributeEnum::bottom_of_pressure) * 0.2 + 70 - c->getSingleAttribute(AttributeEnum::pressure);
        delta[AttributeEnum::is_mental_ill] = -1;
    if (c->getSingleAttribute(AttributeEnum::is_physical_ill))
        delta[AttributeEnum::physical_quality] =
                c->getSingleAttribute(AttributeEnum::top_of_physical_quality) * 0.2 - c->getSingleAttribute(AttributeEnum::physical_quality) + 10;
        delta[AttributeEnum::is_physical_ill] = -1;
    return delta;
}


//ÿѧ��֪ʶˮƽdelta=����ѧϰЧ��+����������-0.7��-������ѹ��-0.4����>0)*0.13;
//ѧϰЧ��delta=-0.15��
//��������delta=-(��5���¼���ѧϰ��task�¼�����*1.5-�˶��¼�����*2+�����¼�����)*0.03;
//����ѹ��delta=(��5���¼���ѧϰ��task�¼�����*2-�˶��¼�����*2-�����¼�����*4)*0.05;
//ע��ɶ���,ʵ����ֵΪ0-100,��Ҫ��������100��
attr DailyEvent::daily_event_study(const Character* c) const {
    attr delta;

    ATTR_TYPE study_rate       = c->getSingleAttribute(AttributeEnum::study_rate);
    ATTR_TYPE physical_quality = c->getSingleAttribute(AttributeEnum::physical_quality);
    ATTR_TYPE pressure         = c->getSingleAttribute(AttributeEnum::pressure);

    //��ȡ��5���¼�ͳ��
    int count_study         = c->getAttributes().getStudy() + c->getAttributes().getTask();
    int count_exercise      = c->getAttributes().getExercise();
    int count_entertainment = c->getAttributes().getEntertainment();

    double delta_knowledge = (study_rate +(physical_quality - 70) - (pressure - 40));
    if (delta_knowledge > 0) delta_knowledge *= 0.115;
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

//ѧϰЧ��delta=0.3-(��5���¼����˶��¼�����-1)*0.15;
//��������delta=0.2;
//����ѹ��delta=-0.15;
//�罻����delta=0.5;
attr DailyEvent::daily_event_exercise(const Character *c) const {
    attr delta;

    //ATTR_TYPE study_rate       = c->getSingleAttribute(AttributeEnum::study_rate);
    //ATTR_TYPE physical_quality = c->getSingleAttribute(AttributeEnum::physical_quality);
    //ATTR_TYPE pressure         = c->getSingleAttribute(AttributeEnum::pressure);

    //��ȡ��5���¼�ͳ��
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

//ѧϰЧ��delta=0.45-����5���¼��������¼�����-1)*0.25;
//��������delta=-0.05��
//����ѹ��delta=-0.2;
//�罻����delta=1;
attr DailyEvent::daily_event_entertainment(const Character *c) const {
    attr delta;

    //ATTR_TYPE study_rate       = c->getSingleAttribute(AttributeEnum::study_rate);
    //ATTR_TYPE physical_quality = c->getSingleAttribute(AttributeEnum::physical_quality);
    //ATTR_TYPE pressure         = c->getSingleAttribute(AttributeEnum::pressure);

    //��ȡ��5���¼�ͳ��
    //int count_study         = c->getAttributes().getStudy() + c->getAttributes().getTask();
    //int count_exercise      = c->getAttributes().getExercise();
    int count_entertainment = c->getAttributes().getEntertainment();
    int corporation_amount = c->getSingleAttribute(AttributeEnum::corporation_amount);

    double delta_study_rate = 45 - (count_entertainment - 1) * 25;

    double delta_physical_quality = -5 + corporation_amount;

    double delta_pressure = -20;

    double delta_social = 50;

    delta[AttributeEnum::study_rate]       = (ATTR_TYPE)delta_study_rate;
    delta[AttributeEnum::physical_quality] = (ATTR_TYPE)delta_physical_quality;
    delta[AttributeEnum::pressure]         = (ATTR_TYPE)delta_pressure;
    delta[AttributeEnum::social]           = (ATTR_TYPE)(delta_social * (1 + corporation_amount * 0.05));

    return delta;
}


//ÿѧ��֪ʶˮƽdelta=����ѧϰЧ��+����������-0.7��-������ѹ��-0.4����>0)*0.09;
//ѧϰЧ��delta=-0.15;
//��������delta=-(��5���¼���ѧϰ��task�¼�����*1.5-�˶��¼�����*2+�����¼�����)*0.03;
//����ѹ��delta=(��5���¼���ѧϰ��task�¼�����*2-�˶��¼�����*2+�����¼�����*4)*0.05;
attr DailyEvent::daily_event_prp(const Character *c) const {
    attr delta;

    ATTR_TYPE study_rate       = c->getSingleAttribute(AttributeEnum::study_rate);
    ATTR_TYPE physical_quality = c->getSingleAttribute(AttributeEnum::physical_quality);
    ATTR_TYPE pressure         = c->getSingleAttribute(AttributeEnum::pressure);

    //��ȡ��5���¼�ͳ��
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

    //��ȡ��5���¼�ͳ��
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
