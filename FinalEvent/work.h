#include<string>
#include<assert.h>

#include "attribute.h"
#include "Character.h"
#include "event.h"

class Work : public Event
{
	attr workContinue(const Character* character) const;

public:
	Work(const std::string& text);

	attr getDelta(const Character* character, const int option) const;

};

Work::Work(const std::string& text) {
	changeText(text);

	optionSet.insertOption(0, "¼ÌÐø");
}

attr Work::getDelta(const Character* character, const int option) const {
	attr result;
	if (option == 0) result = workContinue(character);
	else assert(false);
	return result;
}

attr Work::workContinue(const Character* character) const {
	attr delta;
	return delta;
}

