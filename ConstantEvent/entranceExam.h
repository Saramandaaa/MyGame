#include<string>
#include<assert.h>

#include "attribute.h"
#include "character.h"
#include "event.h"

//�Ż����ɳ�ʼֵ����רҵ�������
class EntranceExam : public Event
{
	attr entranceExamNormallyAttend(const Character* character) const;
public:
	EntranceExam(const std::string& text);

    attr getDelta(const Character* character, const int option) const;

	double getWeight(const Character* character) const;
};

EntranceExam::EntranceExam(const std::string& text) {
    type = EventEnum::entranceExam;
	changeText(text);
	optionSet.insertOption(0, "����");
}

attr EntranceExam::getDelta(const Character* character, const int option) const {
	attr result;
	if (option == 0) result = entranceExamNormallyAttend(character);
	else assert(false);
	return result;
}

double EntranceExam::getWeight(const Character* character) const {
	if (character->getSingleAttribute(AttributeEnum::day) != 1) return 0;
	return weight * 10000;
}

attr EntranceExam::entranceExamNormallyAttend(const Character*) const {
	return attr();
}
