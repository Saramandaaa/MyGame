#include<string>
#include<assert.h>

#include "attribute.h"
#include "Character.h"
#include "event.h"

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
	Prp(const std::string& text);

	attr getDelta(const Character* character, const int option) const;


};

Prp::Prp(const std::string& text) {
	changeText(text);

	optionSet.insertOption(0, "�μ�");
	optionSet.insertOption(1, "���μ�");
}

attr Prp::getDelta(const Character* character, const int option) const {
	attr result;
	if (option == 0) result = prpJoin(character);
	else if (option == 1) result = prpNotJoin(character);
	else assert(false);
	return result;
}

attr Prp::prpJoin(const Character* character) const {
	attr delta;
	delta[AttributeEnum::bottom_of_pressure] = 0.2;
	delta[AttributeEnum::is_of_prp] = 1;
	return delta;
}

attr Prp::prpNotJoin(const Character* character) const {
	attr delta;
	return delta;
}