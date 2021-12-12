#include<string>
#include<assert.h>

#include "Headers/basicheader.h"

//��ѧ��֪ʶˮƽ��������гɼ�=��ѧ��֪ʶˮƽ*100(����100Ҳ��100);
//С��60�յ����棺ѹ������+0.4�������ĩ����ʱ��0��
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
	MidTermExam("���п���")
{

}

MidTermExam::MidTermExam(const std::string& text) {
    type = EventEnum::MidTermExam;
	priority = 3000;
	changeText(text);
	optionSet.insertOption(0, "����");
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
        message = "���п��Բ�����ѹ������";
    }
    else {
        message = "���п��Ժϸ񣬷���:" + std::to_string(grade);
    }
	return delta;
}
