#include<string>
#include<assert.h>

#include "Headers/basicheader.h"

class InnovateFinish : public Event
{
    attr innovateFinishContinue(const Character* character, std::string&) const;

public:
	InnovateFinish();
	InnovateFinish(const std::string& text);

    attr getDelta(const Character* character, const int option, std::string&) const;
	double getWeight(const Character* character) const;
};

InnovateFinish::InnovateFinish() :
    InnovateFinish("大创答辩开始")
{

}

InnovateFinish::InnovateFinish(const std::string& text) {
	type = EventEnum::InnovateFinish;
	priority = 2100;
	changeText(text);
	optionSet.insertOption(0, "继续");
}

attr InnovateFinish::getDelta(const Character* character, const int option, std::string& message) const {
	attr result;
    if (option == 0) result = innovateFinishContinue(character, message);
	else assert(false);
	return result;
}

double InnovateFinish::getWeight(const Character* character) const {
	if (!character->getSingleAttribute(AttributeEnum::is_of_novation)) return 0;
	if (character->getSingleAttribute(AttributeEnum::innovate_term_remain)) return 0;
	return -1;
}

attr InnovateFinish::innovateFinishContinue(const Character* character, std::string& message) const {
	attr delta;
	delta[AttributeEnum::is_of_novation] = -1;
	delta[AttributeEnum::bottom_of_pressure] = -30;
    if (character->getSingleAttribute(AttributeEnum::number_novation) >= 9) {
        delta[AttributeEnum::all_knowledge] = 2 * character->getSingleAttribute(AttributeEnum::number_novation);
		delta[AttributeEnum::scientific_research_time] = 2;
        message = "大创答辩成功完成，科研经历增加，总体知识水平增加";
	}
    else {
        message = "没有认真参与大创项目，答辩失败";
    }
	delta[AttributeEnum::number_novation] = -character->getSingleAttribute(AttributeEnum::number_novation);
	return delta;
}
