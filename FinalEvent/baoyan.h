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

attr Baoyan::baoyanContinue(const Character*) const {
	attr delta;
	return delta;
}

