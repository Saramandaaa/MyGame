#include<string>
#include<assert.h>

#include "Headers/basicheader.h"

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
	InnovateProgram();
	InnovateProgram(const std::string& text);

    attr getDelta(const Character* character, const int option, std::string&) const;
	double getWeight(const Character* character) const;
	
};

InnovateProgram::InnovateProgram() :
    InnovateProgram("�Ƿ�������Ŀ���������Ҫ��3��ѧ���ڽ�������9�δ󴴻��ͨ����硣��ɺ󽫻�ÿ��к�֪ʶ������")
{

}

InnovateProgram::InnovateProgram(const std::string& text) {
    type = EventEnum::InnovateProgram;
	changeText(text);
	optionSet.insertOption(0, "�μ�");
	optionSet.insertOption(1, "���μ�");
}

attr InnovateProgram::getDelta(const Character* character, const int option, std::string&) const {
	attr result;
	if (option == 0) result = innovateProgramJoin(character);
	else if (option == 1) result = innovateProgramNotJoin(character);
	else assert(false);
	return result;
}

double InnovateProgram::getWeight(const Character* character) const {
	if (character->getSingleAttribute(AttributeEnum::randomEventCoolDown)) return 0;
    if (character->getSingleAttribute(AttributeEnum::is_of_prp)) return 0;
	if (character->getSingleAttribute(AttributeEnum::is_of_novation)) return 0;
    if (character->getSingleAttribute(AttributeEnum::term) == 1 || character->getSingleAttribute(AttributeEnum::term) > 5) return 0;
	if (character->getSingleAttribute(AttributeEnum::all_knowledge) < 85 * character->getSingleAttribute(AttributeEnum::term) - 85) return 0;
    return weight;
}

attr InnovateProgram::innovateProgramJoin(const Character*) const {
	attr delta;
	delta[AttributeEnum::randomEventCoolDown] = 1;
	delta[AttributeEnum::is_of_novation] = 1;
    delta[AttributeEnum::bottom_of_pressure] = 30;
	delta[AttributeEnum::innovate_term_remain] = 3;
	return delta;
}

attr InnovateProgram::innovateProgramNotJoin(const Character*) const {
	attr delta;
	delta[AttributeEnum::randomEventCoolDown] = 1;
	return delta;
}
