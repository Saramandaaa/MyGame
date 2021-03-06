#include<string>
#include<assert.h>

#include "Headers/basicheader.h"

//触发概率=压力
//压力下限+0.1；压力归下限+0.1
//触发条件：压力>（上限-下限）*0.8+下限
class MentalDisease : public Event
{
	attr mentalDiseaseContinue(const Character* character) const;

public:
	MentalDisease();
	MentalDisease(const std::string& text);

    attr getDelta(const Character* character, const int option, std::string&) const;

	double getWeight(const Character* character) const;
};

MentalDisease::MentalDisease() :
    MentalDisease("压力过大，出现了心理疾病，压力下限增加，学习效率下降")
{

}

MentalDisease::MentalDisease(const std::string& text) {
    type = EventEnum::mentalDisease;
	changeText(text);

	optionSet.insertOption(0, "继续");
}

attr MentalDisease::getDelta(const Character* character, const int option, std::string&) const {
	attr result;
	if (option == 0) result = mentalDiseaseContinue(character);
	else assert(false);
	return result;
}

double MentalDisease::getWeight(const Character* character) const {
	if (character->getSingleAttribute(AttributeEnum::randomEventCoolDown)) return 0;
	if (character->getSingleAttribute(AttributeEnum::pressure)
		<= character->getSingleAttribute(AttributeEnum::bottom_of_pressure) * 0.2 + 80) return 0;
	double weight = character->getSingleAttribute(AttributeEnum::pressure) * 0.01 * this->weight;
    return weight * 0.5;
}

attr MentalDisease::mentalDiseaseContinue(const Character*) const {
	attr delta;
	delta[AttributeEnum::randomEventCoolDown] = 1;
    delta[AttributeEnum::bottom_of_pressure] = 10;
    delta[AttributeEnum::pressure] = 10;
    delta[AttributeEnum::is_mental_ill] = 1;
	return delta;
}
