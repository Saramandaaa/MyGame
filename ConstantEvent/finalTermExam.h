#include<string>
#include<assert.h>

#include "attribute.h"
#include "character.h"
#include "event.h"

//本学期知识水平输出，期中成绩=本学期知识水平*50(大于100也即100);
//总知识水平delta=期末成绩;
//小于60记录一次挂科(一次挂科则无保研资格，二次挂科则退学);
//一次挂科时，压力下限+0.4

class FinalTermExam : public Event
{
	attr finalTermExamNormallyAttend(const Character* character) const;

public:
	FinalTermExam(const std::string& text);

	attr getDelta(const Character* character, const int option) const;

};

FinalTermExam::FinalTermExam(const std::string& text) {
    type = EventEnum::finalTermExam;
	changeText(text);
	optionSet.insertOption(0, "继续");
}

attr FinalTermExam::getDelta(const Character* character, const int option) const {
	attr result;
	if (option == 0) result = finalTermExamNormallyAttend(character);
	else assert(false);
	return result;
}

attr FinalTermExam::finalTermExamNormallyAttend(const Character* character) const {
	attr delta;
    int finalExamGrade = character->getSingleAttribute(AttributeEnum::all_knowledge);
	if (finalExamGrade < 60) {
        delta[AttributeEnum::bottom_of_pressure] = 40;
		delta[AttributeEnum::failedCourseAmt] = 1;
	}
	return delta;
}
