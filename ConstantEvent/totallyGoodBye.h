#include<string>
#include<assert.h>

#include "attribute.h"
#include "character.h"
#include "event.h"

class TotallyGoodBye : public Event
{
	attr totallyGoodByeContinue(const Character* character) const;
public:
	TotallyGoodBye(const std::string& text);

	attr getDelta(const Character* character, const int option) const;
	double getWeight(const Character* character) const;
};

TotallyGoodBye::TotallyGoodBye(const std::string& text) {
	type = EventEnum::TotallyGoodBye;
	changeText(text);
	optionSet.insertOption(0, "¼ÌĞø");
}

attr TotallyGoodBye::getDelta(const Character* character, const int option) const {
	attr result;
	if (option == 0) result = totallyGoodByeContinue(character);
	else assert(false);
	return result;
}

double TotallyGoodBye::getWeight(const Character* character) const {
	if (character->getSingleAttribute(AttributeEnum::goodByeDay) != 1) return 0;
	return weight * 1000000;
}

attr TotallyGoodBye::totallyGoodByeContinue(const Character* character) const {
	attr delta;
	int learnRate = 100 - character->getSingleAttribute(AttributeEnum::study_rate);
	delta[AttributeEnum::study_rate] = learnRate;
	return delta;
}