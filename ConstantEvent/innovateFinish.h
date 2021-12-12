#include<string>
#include<assert.h>

#include "attribute.h"
#include "character.h"
#include "event.h"

class InnovateFinish : public Event
{
	attr innovateFinishContinue(const Character* character) const;

public:
	InnovateFinish();
	InnovateFinish(const std::string& text);

	attr getDelta(const Character* character, const int option) const;
	double getWeight(const Character* character) const;
};

InnovateFinish::InnovateFinish() :
	InnovateFinish("´ó´´´ð±ç")
{

}

InnovateFinish::InnovateFinish(const std::string& text) {
	type = EventEnum::InnovateFinish;
	priority = 2100;
	changeText(text);
	optionSet.insertOption(0, "¼ÌÐø");
}

attr InnovateFinish::getDelta(const Character* character, const int option) const {
	attr result;
	if (option == 0) result = innovateFinishContinue(character);
	else assert(false);
	return result;
}

double InnovateFinish::getWeight(const Character* character) const {
	if (!character->getSingleAttribute(AttributeEnum::is_of_novation)) return 0;
	if (character->getSingleAttribute(AttributeEnum::innovate_term_remain)) return 0;
	return -1;
}

attr InnovateFinish::innovateFinishContinue(const Character* character) const {
	attr delta;
	delta[AttributeEnum::is_of_novation] = -1;
	delta[AttributeEnum::bottom_of_pressure] = -30;
	if (character->getSingleAttribute(AttributeEnum::number_novation) >= 13) {
		delta[AttributeEnum::all_knowledge] = 6 * character->getSingleAttribute(AttributeEnum::number_novation);
		delta[AttributeEnum::scientific_research_time] = 2;
	}
	delta[AttributeEnum::number_novation] = -character->getSingleAttribute(AttributeEnum::number_novation);
	return delta;
}