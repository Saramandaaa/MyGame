#include<string>
#include<assert.h>

#include "attribute.h"
#include "Character.h"
#include "event.h"

class Withdraw : public Event
{
	attr withdrawContinue(const Character* character) const;

public:
	Withdraw(const std::string& text);

	attr getDelta(const Character* character, const int option) const;

};

Withdraw::Withdraw(const std::string& text) {
	changeText(text);

	optionSet.insertOption(0, "¼ÌÐø");
}

attr Withdraw::getDelta(const Character* character, const int option) const {
	attr result;
	if (option == 0) result = withdrawContinue(character);
	else assert(false);
	return result;
}

attr Withdraw::withdrawContinue(const Character* character) const {
	attr delta;
	return delta;
}
