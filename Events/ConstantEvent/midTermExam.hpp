#include<string>
#include<assert.h>

#include "Headers/basicheader.h"

//本学期知识水平输出，期中成绩=本学期知识水平*100(大于100也即100);
//小于60收到警告：压力下限+0.4（完成期末考试时归0）
class MidTermExam : public Event
{
    attr midTermExamNormallyAttend(const Character* character, std::string&) const;
public:
	MidTermExam();
	MidTermExam(const std::string& text);

    attr getDelta(const Character* character, const int option, std::string&) const;
    double getWeight(const Character* character) const;
};

MidTermExam::MidTermExam() :
	MidTermExam("期中考试")
{

}

MidTermExam::MidTermExam(const std::string& text) {
    type = EventEnum::MidTermExam;
	priority = 3000;
	changeText(text);
	optionSet.insertOption(0, "继续");
}

attr MidTermExam::getDelta(const Character* character, const int option, std::string& message) const {
	attr result;
    if (option == 0) result = midTermExamNormallyAttend(character, message);
	else assert(false);
	return result;
}

double MidTermExam::getWeight(const Character* character) const {
	if (character->getSingleAttribute(AttributeEnum::midTermExamFinish)) return 0;
	if ((character->getSingleAttribute(AttributeEnum::day) - 10) % 20 != 0) return 0;
	return -1;
}

attr MidTermExam::midTermExamNormallyAttend(const Character* character, std::string& message) const {
	attr delta;
	delta[AttributeEnum::midTermExamFinish] = 1;
	int grade = character->getSingleAttribute(AttributeEnum::knowledge);
    if (grade < 60) {
        delta[AttributeEnum::bottom_of_pressure] = 40;
        delta[AttributeEnum::mid_term_failed] = 1;
        message = "期中考试不及格，压力上升";
    }
    else {
        message = "期中考试合格，分数:" + std::to_string(grade);
    }
	return delta;
}
