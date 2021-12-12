#include<string>
#include<assert.h>

#include "Headers/basicheader.h"

class NewTerm : public Event
{
	attr newTermContinue(const Character* character) const;
public:
	NewTerm();
	NewTerm(const std::string& text);

    attr getDelta(const Character* character, int option, std::string&) const;
	double getWeight(const Character* character) const;
};

NewTerm::NewTerm() :
    NewTerm("新的学期开始了")
{

}

NewTerm::NewTerm(const std::string& text) {
	type = EventEnum::newTerm;
	priority = 6000;
	changeText(text);
	optionSet.insertOption(0, "继续");
}

attr NewTerm::getDelta(const Character* character, const int option, std::string&) const {
	attr result;
	if (option == 0) result = newTermContinue(character);
	else assert(false);
	return result;
}

double NewTerm::getWeight(const Character* character) const {
	if (character->getSingleAttribute(AttributeEnum::day) - 20 * character->getSingleAttribute(AttributeEnum::term) != 1) return 0;
	return -1;
}

attr NewTerm::newTermContinue(const Character* character) const {
	attr delta;
	delta[AttributeEnum::term] = 1;
	delta[AttributeEnum::midTermExamFinish] = -character->getSingleAttribute(AttributeEnum::midTermExamFinish);
	delta[AttributeEnum::finalTermExamFinish] = -character->getSingleAttribute(AttributeEnum::finalTermExamFinish);
	if (character->getSingleAttribute(AttributeEnum::is_of_prp)) delta[AttributeEnum::prp_term_remain] = -1;
	if (character->getSingleAttribute(AttributeEnum::is_of_novation)) delta[AttributeEnum::innovate_term_remain] = -1;
	if (character->getSingleAttribute(AttributeEnum::voteCoolDown)) delta[AttributeEnum::voteCoolDown] = -1;
	return delta;
}
