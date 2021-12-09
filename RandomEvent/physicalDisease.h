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
	PhysicalDisease(const std::string& text);

	attr getDelta(const Character* character, const int option) const;

};

PhysicalDisease::PhysicalDisease(const std::string& text) {
    type = EventEnum::physicalDisease;
	changeText(text);

	optionSet.insertOption(0, "����");
}

attr PhysicalDisease::getDelta(const Character* character, const int option) const {
	attr result;
	if (option == 0) result = physicalDiseaseContinue(character);
	else assert(false);
	return result;
}

attr PhysicalDisease::physicalDiseaseContinue(const Character*) const {
	attr delta;
	delta[AttributeEnum::top_of_physical_quality] = -10;
	delta[AttributeEnum::physical_quality] = -10;
	return delta;
}


