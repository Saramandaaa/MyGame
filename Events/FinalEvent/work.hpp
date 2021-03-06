#include<string>
#include<assert.h>

#include "Headers/basicheader.h"

class Work : public Event
{
	attr workContinue(const Character* character) const;

public:
	Work();
	Work(const std::string& text);

    attr getDelta(const Character* character, const int option, std::string&) const;

	double getWeight(const Character* character) const;
};

Work::Work() :
    Work("毕业之后，成为了光荣打工人")
{

}

Work::Work(const std::string& text) {
    type = EventEnum::Work;
	priority = 10000;
	changeText(text);
	optionSet.insertOption(0, "继续");
}

attr Work::getDelta(const Character* character, const int option, std::string&) const {
	attr result;
	if (option == 0) result = workContinue(character);
	else assert(false);
	return result;
}

double Work::getWeight(const Character* character) const {
	if (character->getSingleAttribute(AttributeEnum::day) != 161) return 0;
	return -1;
}

attr Work::workContinue(const Character*) const {
	attr delta;
	return delta;
}

