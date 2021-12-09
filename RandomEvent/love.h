#include<string>
#include<assert.h>

#include "attribute.h"
#include "character.h"
#include "event.h"

//��������=0.01+�罻��*0.005
//������������
//�������ƣ�һ�������ܳ�������
//ѧϰЧ������=1.3;
class Love : public Event
{
	attr loveAccept(const Character* character) const;
	attr loveRefuse(const Character* character) const;

public:
	Love(const std::string& text);

	attr getDelta(const Character* character, const int option) const;

};

Love::Love(const std::string& text) {
    type = EventEnum::Love;
	changeText(text);

	optionSet.insertOption(0, "����");
	optionSet.insertOption(1, "�ܾ�");
}

attr Love::getDelta(const Character* character, const int option) const {
	attr result;
	if (option == 0) result = loveAccept(character);
	else if (option == 1) result = loveRefuse(character);
	else assert(false);
	return result;
}

attr Love::loveAccept(const Character* character) const {
	attr delta;
	delta[AttributeEnum::top_of_study_rate] = 130 - character->getSingleAttribute(AttributeEnum::top_of_study_rate);
	return delta;
}

attr Love::loveRefuse(const Character*) const {
	attr delta;
	return delta;
}
