#include<string>
#include<assert.h>

#include "attribute.h"
#include "character.h"
#include "event.h"

//��ѧ��֪ʶˮƽ�������ĩ�ɼ�=��ѧ��֪ʶˮƽ*50(����100Ҳ��100);
//��֪ʶˮƽdelta=��ĩ�ɼ�;
//С��60��¼һ�ιҿ�(һ�ιҿ����ޱ����ʸ񣬶��ιҿ�����ѧ);
//һ�ιҿ�ʱ��ѹ������+0.4

class FinalTermExam : public Event
{
    attr finalTermExamNormallyAttend(const Character* character, std::string&) const;

public:
	FinalTermExam();
	FinalTermExam(const std::string& text);

    attr getDelta(const Character* character, const int option, std::string&) const;
	double getWeight(const Character* character) const;
};

FinalTermExam::FinalTermExam() :
	FinalTermExam("��ĩ����")
{

}

FinalTermExam::FinalTermExam(const std::string& text) {
    type = EventEnum::finalTermExam;
	priority = 4000;
	changeText(text);
	optionSet.insertOption(0, "����");
}

attr FinalTermExam::getDelta(const Character* character, const int option, std::string& message) const {
	attr result;
    if (option == 0) result = finalTermExamNormallyAttend(character, message);
	else assert(false);
	return result;
}

double FinalTermExam::getWeight(const Character* character) const {
	if (character->getSingleAttribute(AttributeEnum::finalTermExamFinish)) return 0;
	if (character->getSingleAttribute(AttributeEnum::day) % 20 != 0) return 0;
	return -1;
}

attr FinalTermExam::finalTermExamNormallyAttend(const Character* character, std::string& message) const {
	attr delta;
	delta[AttributeEnum::finalTermExamFinish] = 1;
    int finalExamGrade = 0.5 * character->getSingleAttribute(AttributeEnum::knowledge);
	if (finalExamGrade < 60) {
        delta[AttributeEnum::bottom_of_pressure] = 40;
		delta[AttributeEnum::failedCourseAmt] = 1;
        message = "��ĩ���Բ�������ѧ���棬ѹ������";
	}
    else {
        message = "��ĩ���Ժϸ񣬷���:" + std::to_string(finalExamGrade);
    }
    if (character->getSingleAttribute(AttributeEnum::mid_term_failed)) {
        delta[AttributeEnum::bottom_of_pressure] -= 40;
        delta[AttributeEnum::mid_term_failed] = -1;
    }
    delta[AttributeEnum::all_knowledge] = finalExamGrade;
    delta[AttributeEnum::knowledge] = -character->getSingleAttribute(AttributeEnum::knowledge);

	return delta;
}
