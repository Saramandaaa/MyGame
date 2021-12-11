#include<string>
#include<assert.h>

#include "attribute.h"
#include "character.h"
#include "event.h"

class Work : public Event
{
	attr workContinue(const Character* character) const;

public:
	Work(const std::string& text);

	attr getDelta(const Character* character, const int option) const;

	double getWeight(const Character* character) const;
};

Work::Work(const std::string& text) {
    type = EventEnum::Work;
	changeText(text);
	optionSet.insertOption(0, "¼ÌÐø");
}

attr Work::getDelta(const Character* character, const int option) const {
	attr result;
	if (option == 0) result = workContinue(character);
	else assert(false);
	return result;
}

double Work::getWeight(const Character* character) const {
	if (character->getSingleAttribute(AttributeEnum::day) != 1008) return 0;
	return weight * 1000000;
}

attr Work::workContinue(const Character*) const {
	attr delta;
	return delta;
}

