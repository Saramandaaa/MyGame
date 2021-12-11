#include<string>
#include<assert.h>

#include "attribute.h"
#include "character.h"
#include "event.h"

//触发概率=0.5+社交力*0.1;
//触发条件：仅在第一学期期中后的第一个日常事件
//学习效率=1;
class JoinCorporation : public Event
{
	attr joinCorporationJoin(const Character* character) const;
	attr joinCorporationNotJoin(const Character* character) const;

public:
	JoinCorporation(const std::string& text);

	attr getDelta(const Character* character, const int option) const;
	double getWeight(const Character* character) const;
};

JoinCorporation::JoinCorporation(const std::string& text) {
    type = EventEnum::JoinCorporation;
	changeText(text);
	optionSet.insertOption(0, "加入");
	optionSet.insertOption(1, "不加入");
}

attr JoinCorporation::getDelta(const Character* character, const int option) const {
	attr result;
	if (option == 0) result = joinCorporationJoin(character);
	else if (option == 1) result = joinCorporationNotJoin(character);
	else assert(false);
	return result;
}

double JoinCorporation::getWeight(const Character* character) const {
	if (character->getSingleAttribute(AttributeEnum::day) != 63) return 0;
	double weight = (0.5 + character->getSingleAttribute(AttributeEnum::social) * 0.00e1) * this->weight;
	return weight;
}

attr JoinCorporation::joinCorporationJoin(const Character*) const {
	attr delta;
	delta[AttributeEnum::study_rate] = 100;
	return delta;
}
attr JoinCorporation::joinCorporationNotJoin(const Character*) const {
	attr delta;
	return delta;
}
