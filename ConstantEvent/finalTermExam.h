#include<string>
#include<assert.h>

#include "attribute.h"
#include "character.h"
#include "event.h"

//��ѧ��֪ʶˮƽ��������гɼ�=��ѧ��֪ʶˮƽ*50(����100Ҳ��100);
//��֪ʶˮƽdelta=��ĩ�ɼ�;
//С��60��¼һ�ιҿ�(һ�ιҿ����ޱ����ʸ񣬶��ιҿ�����ѧ);
//һ�ιҿ�ʱ��ѹ������+0.4

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
	optionSet.insertOption(0, "����");
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
