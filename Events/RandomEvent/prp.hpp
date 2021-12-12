#include<string>
#include<assert.h>

#include "Headers/basicheader.h"

//������������֪ʶˮƽ����>=80(��ǰѧ����-1)��ÿ��ѧ�ڣ���һѧ�ڳ��⣩��ʼ
//����daily_event_prptask����ʱ����ѧ��
//ѹ������+0.2�����ʱ��0��
//������������8��daily_event_prptask
//��ɽ��������о���+1����֪ʶˮƽ����delta=���daily_event_prptask����*4
//ע��prp��innovate_program������

class Prp : public Event
{
	attr prpJoin(const Character* character) const;
	attr prpNotJoin(const Character* character) const;
public:
	Prp();
	Prp(const std::string& text);

    attr getDelta(const Character* character, const int option, std::string&) const;

	double getWeight(const Character* character) const;

};

Prp::Prp() :
    Prp("�Ƿ����PRP��Ŀ���������Ҫ��2��ѧ���ڽ�������6��PRP���ͨ����硣��ɺ󽫻�ÿ��к�֪ʶ����")
{

}

Prp::Prp(const std::string& text) {
    type = EventEnum::Prp;
	changeText(text);

	optionSet.insertOption(0, "�μ�");
	optionSet.insertOption(1, "���μ�");
}

attr Prp::getDelta(const Character* character, const int option, std::string&) const {
	attr result;
	if (option == 0) result = prpJoin(character);
	else if (option == 1) result = prpNotJoin(character);
	else assert(false);
	return result;
}

double Prp::getWeight(const Character* character) const {
	if (character->getSingleAttribute(AttributeEnum::randomEventCoolDown)) return 0;
    if (character->getSingleAttribute(AttributeEnum::is_of_novation)) return 0;
	if (character->getSingleAttribute(AttributeEnum::is_of_prp)) return 0;
    if (character->getSingleAttribute(AttributeEnum::term) == 1 || character->getSingleAttribute(AttributeEnum::term) > 6) return 0;
	if (character->getSingleAttribute(AttributeEnum::all_knowledge) < 80 * character->getSingleAttribute(AttributeEnum::term) - 80) return 0;
	return weight;
}

attr Prp::prpJoin(const Character*) const {
	attr delta;
	delta[AttributeEnum::randomEventCoolDown] = 1;
    delta[AttributeEnum::bottom_of_pressure] = 20;
	delta[AttributeEnum::is_of_prp] = 1;
	delta[AttributeEnum::prp_term_remain] = 2;
	return delta;
}

attr Prp::prpNotJoin(const Character*) const {
	attr delta;
	delta[AttributeEnum::randomEventCoolDown] = 1;
	return delta;
}