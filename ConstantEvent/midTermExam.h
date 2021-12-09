#include<string>
#include<assert.h>

#include "attribute.h"
#include "Character.h"
#include "event.h"

//本学期知识水平输出，期中成绩=本学期知识水平*100(大于100也即100);
//小于60收到警告：压力下限+0.4（完成期末考试时归0）
class MidTermExam : public Event
{
	attr midTermExamNormallyAttend(const Character* character) const;
public:
	MidTermExam(const std::string& text);

	attr getDelta(const Character* character, const int option) const;
};

MidTermExam::MidTermExam(const std::string& text) {
	changeText(text);

	optionSet.insertOption(0, "继续");
}

attr MidTermExam::getDelta(const Character* character, const int option) const {
	attr result;
	if (option == 0) result = midTermExamNormallyAttend(character);
	else assert(false);
	return result;
}

attr MidTermExam::midTermExamNormallyAttend(const Character* character) const {
	attr delta;
	int grade = character->getSingleAttribute(AttributeEnum::knowledge);
	if (grade < 60) delta[AttributeEnum::bottom_of_pressure] = 0.4;
	return delta;
}