#include<string>
#include<assert.h>

#include "attribute.h"
#include "Character.h"
#include "event.h"

//��������=0.1
//����������ѹ��>0.7
//�������ƣ�����love֮�󴥷�
//ѧϰЧ������=0.7(10���¼����1)
class SayGoodBye : public Event
{
	attr sayGoodByeContinue(const Character* character) const;

public:
	SayGoodBye(const std::string& text);

	attr getDelta(const Character* character, const int optino) const;

};

SayGoodBye::SayGoodBye(const std::string& text) {
	changeText(text);

	optionSet.insertOption(0, "����");
}

attr SayGoodBye::getDelta(const Character* character, const int option) const {
	attr result;
	if (option == 0) result = sayGoodByeContinue(character);
	else assert(false);
	return result;
}

attr SayGoodBye::sayGoodByeContinue(const Character* character) const {
	attr delta;
	delta[AttributeEnum::top_of_study_rate] = 70 - character->getSingleAttribute(AttributeEnum::top_of_study_rate);
	return delta;
}
