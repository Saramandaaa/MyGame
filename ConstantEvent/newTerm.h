#include<string>
#include<assert.h>

#include "attribute.h"
#include "character.h"
#include "event.h"

class NewTerm : public Event
{
	attr newTermContinue(const Character* character) const;
public:
	NewTerm(const std::string& text);

	attr getDelta(const Character* character, int option) const;
	double getWeight(const Character* character) const;
};

NewTerm::NewTerm(const std::string& text) {
	type = EventEnum::newTerm;
	changeText(text);
	optionSet.insertOption(0, "¼ÌÐø");
}

attr NewTerm::getDelta(const Character* character, const int option) const {
	attr result;
	if (option == 0) result = newTermContinue(character);
	else assert(false);
	return result;
}

double NewTerm::getWeight(const Character* character) const {
	if (character->getSingleAttribute(AttributeEnum::day) % 126 != 0) return 0;
	return weight * 10000;
}

attr NewTerm::newTermContinue(const Character* character) const {
	attr delta;
	delta[AttributeEnum::term] = 1;
	if (character->getSingleAttribute(AttributeEnum::is_of_prp)) delta[AttributeEnum::prp_term_remain] = -1;
	if (character->getSingleAttribute(AttributeEnum::is_of_novation)) delta[AttributeEnum::innovate_term_remain] = -1;
	if (character->getSingleAttribute(AttributeEnum::voteCoolDown)) delta[AttributeEnum::voteCoolDown] = -1;
	return delta;
}