#include<string>
#include<assert.h>

#include "attribute.h"
#include "character.h"
#include "event.h"

//��������=��������������-��ǰ�������ʣ�/�������������ޣ�+��1-�����������ޣ�
//������������-0.1���������ʹ�����-0.1
//������������������<������-���ޣ�*0.2
class PhysicalDisease : public Event
{
	attr physicalDiseaseContinue(const Character* character) const;

public:
	PhysicalDisease();
	PhysicalDisease(const std::string& text);

    attr getDelta(const Character* character, const int option, std::string&) const;
	double getWeight(const Character* character) const;

};

PhysicalDisease::PhysicalDisease() :
    PhysicalDisease("���ڳ��ڲ��������������ʽϲ�������ˣ��������ʼ�������")
{

}

PhysicalDisease::PhysicalDisease(const std::string& text) {
    type = EventEnum::physicalDisease;
	changeText(text);

	optionSet.insertOption(0, "����");
}

attr PhysicalDisease::getDelta(const Character* character, const int option, std::string&) const {
	attr result;
	if (option == 0) result = physicalDiseaseContinue(character);
	else assert(false);
	return result;
}

double PhysicalDisease::getWeight(const Character* character) const {
	if (character->getSingleAttribute(AttributeEnum::randomEventCoolDown)) return 0;
	if (character->getSingleAttribute(AttributeEnum::physical_quality)
		>= character->getSingleAttribute(AttributeEnum::top_of_physical_quality) * 0.2) return 0;
	double weight = (101
		- (double)character->getSingleAttribute(AttributeEnum::top_of_physical_quality)
		- 100 * (double)character->getSingleAttribute(AttributeEnum::physical_quality) / character->getSingleAttribute(AttributeEnum::top_of_physical_quality))
		* this->weight;
	return weight;
}

attr PhysicalDisease::physicalDiseaseContinue(const Character*) const {
	attr delta;
	delta[AttributeEnum::randomEventCoolDown] = 1;
	delta[AttributeEnum::top_of_physical_quality] = -10;
	delta[AttributeEnum::physical_quality] = -10;
    delta[AttributeEnum::is_physical_ill] = 1;
	return delta;
}


