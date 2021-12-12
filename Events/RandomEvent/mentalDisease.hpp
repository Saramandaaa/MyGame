#include<string>
#include<assert.h>

#include "Headers/basicheader.h"

//��������=ѹ��
//ѹ������+0.1��ѹ��������+0.1
//����������ѹ��>������-���ޣ�*0.8+����
class MentalDisease : public Event
{
	attr mentalDiseaseContinue(const Character* character) const;

public:
	MentalDisease();
	MentalDisease(const std::string& text);

    attr getDelta(const Character* character, const int option, std::string&) const;

	double getWeight(const Character* character) const;
};

MentalDisease::MentalDisease() :
    MentalDisease("ѹ�����󣬳���������������ѹ���������ӣ�ѧϰЧ���½�")
{

}

MentalDisease::MentalDisease(const std::string& text) {
    type = EventEnum::mentalDisease;
	changeText(text);

	optionSet.insertOption(0, "����");
}

attr MentalDisease::getDelta(const Character* character, const int option, std::string&) const {
	attr result;
	if (option == 0) result = mentalDiseaseContinue(character);
	else assert(false);
	return result;
}

double MentalDisease::getWeight(const Character* character) const {
	if (character->getSingleAttribute(AttributeEnum::randomEventCoolDown)) return 0;
	if (character->getSingleAttribute(AttributeEnum::pressure)
		<= character->getSingleAttribute(AttributeEnum::bottom_of_pressure) * 0.2 + 80) return 0;
	double weight = character->getSingleAttribute(AttributeEnum::pressure) * 0.01 * this->weight;
    return weight * 0.5;
}

attr MentalDisease::mentalDiseaseContinue(const Character*) const {
	attr delta;
	delta[AttributeEnum::randomEventCoolDown] = 1;
    delta[AttributeEnum::bottom_of_pressure] = 10;
    delta[AttributeEnum::pressure] = 10;
    delta[AttributeEnum::is_mental_ill] = 1;
	return delta;
}