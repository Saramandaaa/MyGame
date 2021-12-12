#include<string>
#include<assert.h>

#include "attribute.h"
#include "character.h"
#include "event.h"

class Baoyan : public Event
{
	attr baoyanContinue(const Character* character) const;

public:
	Baoyan();
	Baoyan(const std::string& text);

	attr getDelta(const Character* character, const int option) const;
	double getWeight(const Character* character) const;

};

Baoyan::Baoyan() :
	Baoyan("保研人上人")
{

}

Baoyan::Baoyan(const std::string& text) {
    type = EventEnum::Baoyan;
	priority = 30000;
	changeText(text);
	optionSet.insertOption(0, "继续");
}

attr Baoyan::getDelta(const Character* character, const int option) const {
	attr result;
	if (option == 0) result = baoyanContinue(character);
	else assert(false);
	return result;
}

double Baoyan::getWeight(const Character* character) const {
	if (character->getSingleAttribute(AttributeEnum::day) != 161) return 0;
	if (character->getSingleAttribute(AttributeEnum::scientific_research_time) < 1
		|| character->getSingleAttribute(AttributeEnum::failedCourseAmt) >= 1
		|| character->getSingleAttribute(AttributeEnum::all_knowledge) < 720) return 0;
	return -1;
}

attr Baoyan::baoyanContinue(const Character*) const {
	attr delta;
	return delta;
}

