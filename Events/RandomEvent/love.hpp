#include<string>
#include<assert.h>

#include "Headers/basicheader.h"

//触发概率=0.01+社交力*0.005
//触发条件：无
//触发限制：一共仅可能出现3次
//学习效率上限=1.3;
class Love : public Event
{
	attr loveAccept(const Character* character) const;
	attr loveRefuse(const Character* character) const;

public:
	Love();
	Love(const std::string& text);

    attr getDelta(const Character* character, const int option, std::string&) const;
	double getWeight(const Character* character) const;
};

Love::Love() :
    Love("有机会与一位异性坠入爱河，是否接受？")
{

}

Love::Love(const std::string& text) {
    type = EventEnum::Love;
	changeText(text);

	optionSet.insertOption(0, "接受");
	optionSet.insertOption(1, "拒绝");
}

attr Love::getDelta(const Character* character, const int option, std::string&) const {
	attr result;
	if (option == 0) result = loveAccept(character);
	else if (option == 1) result = loveRefuse(character);
	else assert(false);
	return result;
}

double Love::getWeight(const Character* character) const {
	if (character->getSingleAttribute(AttributeEnum::randomEventCoolDown)) return 0;
	if (character->getSingleAttribute(AttributeEnum::is_of_love)) return 0;
    if (character->getSingleAttribute(AttributeEnum::number_love) >= 3) return 0;
    double weight = (0.01 + character->getSingleAttribute(AttributeEnum::social) * 0.005) * this->weight;
    int day = character->getSingleAttribute(AttributeEnum::goodByeDay);
    if (day) weight *= (1 - day / 11.0);
    return weight;
}

attr Love::loveAccept(const Character* character) const {
	attr delta;
	delta[AttributeEnum::randomEventCoolDown] = 1;
	delta[AttributeEnum::top_of_study_rate] = 130 - character->getSingleAttribute(AttributeEnum::top_of_study_rate);
	delta[AttributeEnum::is_of_love] = 1;
	delta[AttributeEnum::number_love] = 1;
	if (character->getSingleAttribute(AttributeEnum::goodByeDay)) delta[AttributeEnum::goodByeDay] = -character->getSingleAttribute(AttributeEnum::goodByeDay);
	return delta;
}

attr Love::loveRefuse(const Character*) const {
	attr delta;
	delta[AttributeEnum::randomEventCoolDown] = 1;
    delta[AttributeEnum::number_love] = 1;
	return delta;
}
