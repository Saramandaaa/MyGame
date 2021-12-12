#include<string>
#include<assert.h>

#include "attribute.h"
#include "character.h"
#include "event.h"

class TotallyGoodBye : public Event
{
	attr totallyGoodByeContinue(const Character* character) const;
public:
	TotallyGoodBye();
	TotallyGoodBye(const std::string& text);

	attr getDelta(const Character* character, const int option) const;
	double getWeight(const Character* character) const;
};

TotallyGoodBye::TotallyGoodBye() :
	TotallyGoodBye("彻底与过去告别")
{

}

TotallyGoodBye::TotallyGoodBye(const std::string& text) {
	type = EventEnum::TotallyGoodBye;
	priority = 1000;
	changeText(text);
	optionSet.insertOption(0, "继续");
}

attr TotallyGoodBye::getDelta(const Character* character, const int option) const {
	attr result;
	if (option == 0) result = totallyGoodByeContinue(character);
	else assert(false);
	return result;
}

double TotallyGoodBye::getWeight(const Character* character) const {
	if (character->getSingleAttribute(AttributeEnum::goodByeDay) != 1) return 0;
	return -1;
}

attr TotallyGoodBye::totallyGoodByeContinue(const Character* character) const {
	attr delta;
	delta[AttributeEnum::goodByeDay] = -1;
	int learnRate = 100 - character->getSingleAttribute(AttributeEnum::study_rate);
	delta[AttributeEnum::study_rate] = learnRate;
	return delta;
}