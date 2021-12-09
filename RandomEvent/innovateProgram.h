#include<string>
#include<assert.h>

#include "attribute.h"
#include "Character.h"
#include "event.h"

//������������֪ʶˮƽ����>=85(��ǰѧ����-1)��ÿ��ѧ�ڣ���һѧ�ڳ��⣩��ʼ
//����daily_event_novationtask����ʱ����ѧ��
//ѹ������+0.3�����ʱ��0��
//������������13��daily_event_novationtask
//��ɽ��������о���+2����֪ʶˮƽ����delta=���daily_event_prptask����*6
//ע��prp��innovate_program������
class InnovateProgram : public Event
{
	attr innovateProgramJoin(const Character* character) const;
	attr innovateProgramNotJoin(const Character* character) const;

public:
	InnovateProgram(const std::string& text);

	attr getDelta(const Character* character, const int option) const;
	
};

InnovateProgram::InnovateProgram(const std::string& text) {
	changeText(text);

	optionSet.insertOption(0, "�μ�");
	optionSet.insertOption(1, "���μ�");
}

attr InnovateProgram::getDelta(const Character* character, const int option) const {
	attr result;
	if (option == 0) result = innovateProgramJoin(character);
	else if (option == 1) result = innovateProgramNotJoin(character);
	else assert(false);
	return result;
}

attr InnovateProgram::innovateProgramJoin(const Character* character) const {
	attr delta;
	delta[AttributeEnum::is_of_novation] = 1;
	delta[AttributeEnum::bottom_of_pressure] = 0.3;
	return delta;
}

attr InnovateProgram::innovateProgramNotJoin(const Character* character) const {
	attr delta;
	return delta;
}