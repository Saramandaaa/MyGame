#include<string>
#include<assert.h>

#include "attribute.h"
#include "character.h"
#include "event.h"

//触发概率=0.1
//触发条件：压力>0.7
//触发限制：仅在love之后触发
//学习效率上限=0.7(10次事件后归1)
class SayGoodBye : public Event
{
	attr sayGoodByeContinue(const Character* character) const;

public:
	SayGoodBye(const std::string& text);

	attr getDelta(const Character* character, const int optino) const;
	double getWeight(const Character* character) const;

};

SayGoodBye::SayGoodBye(const std::string& text) {
    type = EventEnum::sayGoodBye;
	changeText(text);

	optionSet.insertOption(0, "继续");
}

attr SayGoodBye::getDelta(const Character* character, const int option) const {
	attr result;
	if (option == 0) result = sayGoodByeContinue(character);
	else assert(false);
	return result;
}

double SayGoodBye::getWeight(const Character* character) const {
	if (!character->getSingleAttribute(AttributeEnum::is_of_love)) return 0;
	if (character->getSingleAttribute(AttributeEnum::pressure) <= 70) return 0;
	double weight = 0.1 * this->weight;
	return weight;
}

attr SayGoodBye::sayGoodByeContinue(const Character* character) const {
	attr delta;
	delta[AttributeEnum::is_of_love] = -1;
	delta[AttributeEnum::top_of_study_rate] = 70 - character->getSingleAttribute(AttributeEnum::top_of_study_rate);
	delta[AttributeEnum::goodByeDay] = 10;
	return delta;
}
