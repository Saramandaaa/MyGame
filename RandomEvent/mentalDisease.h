#include<string>
#include<assert.h>

#include "attribute.h"
#include "character.h"
#include "event.h"

//触发概率=压力
//压力下限+0.1；压力归下限+0.1
//触发条件：压力>（上限-下限）*0.8+下限
class MentalDisease : public Event
{
	attr mentalDiseaseContinue(const Character* character) const;

public:
	MentalDisease();
	MentalDisease(const std::string& text);

	attr getDelta(const Character* character, const int option) const;

	double getWeight(const Character* character) const;
};

MentalDisease::MentalDisease() :
	MentalDisease("玉玉症")
{

}

MentalDisease::MentalDisease(const std::string& text) {
    type = EventEnum::mentalDisease;
	changeText(text);

	optionSet.insertOption(0, "继续");
}

attr MentalDisease::getDelta(const Character* character, const int option) const {
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
	return weight;
}

attr MentalDisease::mentalDiseaseContinue(const Character*) const {
	attr delta;
	delta[AttributeEnum::randomEventCoolDown] = 1;
    delta[AttributeEnum::bottom_of_pressure] = 10;
    delta[AttributeEnum::pressure] = 10;
	return delta;
}
