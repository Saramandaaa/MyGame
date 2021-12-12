#include<string>
#include<assert.h>

#include "attribute.h"
#include "character.h"
#include "event.h"

//优化：由初始值决定专业分流情况
class EntranceExam : public Event
{
	attr entranceExamNormallyAttend(const Character* character) const;
public:
	EntranceExam();
	EntranceExam(const std::string& text);

    attr getDelta(const Character* character, const int option, std::string&) const;

	double getWeight(const Character* character) const;
};

EntranceExam::EntranceExam() :
	EntranceExam("入学考试，决定你的大学学习方向")
{

}

EntranceExam::EntranceExam(const std::string& text) {
    type = EventEnum::entranceExam;
	priority = 5000;
	changeText(text);
	optionSet.insertOption(0, "继续");
}

attr EntranceExam::getDelta(const Character* character, const int option, std::string&) const {
	attr result;
	if (option == 0) result = entranceExamNormallyAttend(character);
	else assert(false);
	return result;
}

double EntranceExam::getWeight(const Character* character) const {
	if (character->getSingleAttribute(AttributeEnum::day) != 2 || character->getSingleAttribute(AttributeEnum::entranceExamFinish)) return 0;
	return -1;
}

attr EntranceExam::entranceExamNormallyAttend(const Character*) const {
	attr delta;
	delta[AttributeEnum::entranceExamFinish] = 1;
	return delta;
}
