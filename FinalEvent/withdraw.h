#include<string>
#include<assert.h>

#include "attribute.h"
#include "character.h"
#include "event.h"

class Withdraw : public Event
{
	attr withdrawContinue(const Character* character) const;

public:
	Withdraw(const std::string& text);

	attr getDelta(const Character* character, const int option) const;
	double getWeight(const Character* character) const;

};

Withdraw::Withdraw(const std::string& text) {
    type = EventEnum::Withdraw;
	changeText(text);
	optionSet.insertOption(0, "����");
}

attr Withdraw::getDelta(const Character* character, const int option) const {
	attr result;
	if (option == 0) result = withdrawContinue(character);
	else assert(false);
	return result;
}

double Withdraw::getWeight(const Character* character) const {
	if (character->getSingleAttribute(AttributeEnum::failedCourseAmt) < 2) return 0;
	return weight * 1000000;
}

attr Withdraw::withdrawContinue(const Character*) const {
	attr delta;
	return delta;
}
