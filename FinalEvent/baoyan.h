#include<string>
#include<assert.h>

#include "attribute.h"
#include "character.h"
#include "event.h"

class Baoyan : public Event
{
	attr baoyanContinue(const Character* character) const;

public:
	Baoyan(const std::string& text);

	attr getDelta(const Character* character, const int option) const;
	double getWeight(const Character* character) const;

};

Baoyan::Baoyan(const std::string& text) {
    type = EventEnum::Baoyan;
	changeText(text);
	optionSet.insertOption(0, "¼ÌÐø");
}

attr Baoyan::getDelta(const Character* character, const int option) const {
	attr result;
	if (option == 0) result = baoyanContinue(character);
	else assert(false);
	return result;
}

double Baoyan::getWeight(const Character* character) const {
	if (character->getSingleAttribute(AttributeEnum::day) != 1008) return 0;
	if (character->getSingleAttribute(AttributeEnum::scientific_research_time) < 1
		|| character->getSingleAttribute(AttributeEnum::failedCourseAmt) >= 1
		|| character->getSingleAttribute(AttributeEnum::all_knowledge) < 720) return 0;
	return weight * 100000000;
}

attr Baoyan::baoyanContinue(const Character*) const {
	attr delta;
	return delta;
}

