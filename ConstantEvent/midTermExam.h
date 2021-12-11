#include<string>
#include<assert.h>

#include "attribute.h"
#include "character.h"
#include "event.h"

//��ѧ��֪ʶˮƽ��������гɼ�=��ѧ��֪ʶˮƽ*100(����100Ҳ��100);
//С��60�յ����棺ѹ������+0.4�������ĩ����ʱ��0��
class MidTermExam : public Event
{
	attr midTermExamNormallyAttend(const Character* character) const;
public:
	MidTermExam(const std::string& text);

	attr getDelta(const Character* character, const int option) const;
	double getWeight(const Character* character) const;
};

MidTermExam::MidTermExam(const std::string& text) {
    type = EventEnum::MidTermExam;
	changeText(text);
	optionSet.insertOption(0, "����");
}

attr MidTermExam::getDelta(const Character* character, const int option) const {
	attr result;
	if (option == 0) result = midTermExamNormallyAttend(character);
	else assert(false);
	return result;
}

double MidTermExam::getWeight(const Character* character) const {
	if ((character->getSingleAttribute(AttributeEnum::day) - 62) % 126) return 0;
	return weight * 10000;
}

attr MidTermExam::midTermExamNormallyAttend(const Character* character) const {
	attr delta;
	int grade = character->getSingleAttribute(AttributeEnum::knowledge);
    if (grade < 60) delta[AttributeEnum::bottom_of_pressure] = 40;
	return delta;
}
