#include<string>
#include<assert.h>

#include "attribute.h"
#include "Character.h"
#include "event.h"

//��������=ѹ��
//ѹ������+0.1��ѹ��������+0.1
//����������ѹ��>������-���ޣ�*0.8+����
class MentalDisease : public Event
{
	attr mentalDiseaseContinue(const Character* character) const;

public:

	MentalDisease(const std::string& text);

	attr getDelta(const Character* character, const int option) const;

};

MentalDisease::MentalDisease(const std::string& text) {
	changeText(text);

	optionSet.insertOption(0, "����");
}

attr MentalDisease::getDelta(const Character* character, const int option) const {
	attr result;
	if (option == 0) result = mentalDiseaseContinue(character);
	else assert(false);
	return result;
}

attr MentalDisease::mentalDiseaseContinue(const Character* character) const {
	attr delta;
	delta[AttributeEnum::bottom_of_pressure] = 0.1;
	delta[AttributeEnum::pressure] = 0.1;
	return delta;
}