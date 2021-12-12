#include<string>
#include<assert.h>

#include "attribute.h"
#include "character.h"
#include "event.h"

class PrpFinish : public Event
{
    attr prpFinishContinue(const Character* character, std::string&) const;

public:
	PrpFinish();
	PrpFinish(const std::string& text);

    attr getDelta(const Character* character, const int option, std::string&) const;
	double getWeight(const Character* character) const;
};

PrpFinish::PrpFinish() :
    PrpFinish("PRP��翪ʼ")
{

}

PrpFinish::PrpFinish(const std::string& text) {
	type = EventEnum::PrpFinish;
	priority = 2000;
	changeText(text);
	optionSet.insertOption(0, "����");
}

attr PrpFinish::getDelta(const Character* character, const int option, std::string& message) const {
	attr result;
    if (option == 0) result = prpFinishContinue(character, message);
	else assert(false);
	return result;
}

double PrpFinish::getWeight(const Character* character) const {
	if (!character->getSingleAttribute(AttributeEnum::is_of_prp)) return 0;
	if (character->getSingleAttribute(AttributeEnum::prp_term_remain)) return 0;
	return -1;
}

attr PrpFinish::prpFinishContinue(const Character* character, std::string& message) const {
	attr delta;
	delta[AttributeEnum::is_of_prp] = -1;
	delta[AttributeEnum::bottom_of_pressure] = -20;
    if (character->getSingleAttribute(AttributeEnum::number_prp) >= 6) {
		delta[AttributeEnum::all_knowledge] = 4 * character->getSingleAttribute(AttributeEnum::number_prp);
		delta[AttributeEnum::scientific_research_time] = 1;
        message = "PRP���ɹ���ɣ����о������ӣ�����֪ʶˮƽ����";
	}
    else {
        message = "û���������PRP��Ŀ�����ʧ��";
    }
	delta[AttributeEnum::number_prp] = -character->getSingleAttribute(AttributeEnum::number_prp);
	return delta;
}
