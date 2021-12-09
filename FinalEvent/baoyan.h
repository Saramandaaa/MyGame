#include<string>
#include<assert.h>

#include "attribute.h"
#include "Character.h"
#include "event.h"

class Baoyan : public Event
{
	attr baoyanContinue(const Character* character) const;

public:
	Baoyan(const std::string& text);

	attr getDelta(const Character* character, const int option) const;

};

Baoyan::Baoyan(const std::string& text) {
	changeText(text);

	optionSet.insertOption(0, "¼ÌÐø");
}

attr Baoyan::getDelta(const Character* character, const int option) const {
	attr result;
	if (option == 0) result = baoyanContinue(character);
	else assert(false);
	return result;
}

attr Baoyan::baoyanContinue(const Character* character) const {
	attr delta;
	return delta;
}

