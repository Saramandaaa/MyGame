#include<string>
#include<assert.h>

#include "attribute.h"
#include "character.h"
#include "event.h"

//触发概率=（身体素质上限-当前身体素质）/（身体素质上限）+（1-身体素质上限）
//身体素质上限-0.1；身体素质归上限-0.1
//触发条件：身体素质<（上限-下限）*0.2
class PhysicalDisease : public Event
{
	attr physicalDiseaseContinue(const Character* character) const;

public:
	PhysicalDisease();
	PhysicalDisease(const std::string& text);

    attr getDelta(const Character* character, const int option, std::string&) const;
	double getWeight(const Character* character) const;

};

PhysicalDisease::PhysicalDisease() :
    PhysicalDisease("由于长期不锻炼，身体素质较差，你生病了，身体素质继续降低")
{

}

PhysicalDisease::PhysicalDisease(const std::string& text) {
    type = EventEnum::physicalDisease;
	changeText(text);

	optionSet.insertOption(0, "继续");
}

attr PhysicalDisease::getDelta(const Character* character, const int option, std::string&) const {
	attr result;
	if (option == 0) result = physicalDiseaseContinue(character);
	else assert(false);
	return result;
}

double PhysicalDisease::getWeight(const Character* character) const {
	if (character->getSingleAttribute(AttributeEnum::randomEventCoolDown)) return 0;
	if (character->getSingleAttribute(AttributeEnum::physical_quality)
		>= character->getSingleAttribute(AttributeEnum::top_of_physical_quality) * 0.2) return 0;
	double weight = (101
		- (double)character->getSingleAttribute(AttributeEnum::top_of_physical_quality)
		- 100 * (double)character->getSingleAttribute(AttributeEnum::physical_quality) / character->getSingleAttribute(AttributeEnum::top_of_physical_quality))
		* this->weight;
	return weight;
}

attr PhysicalDisease::physicalDiseaseContinue(const Character*) const {
	attr delta;
	delta[AttributeEnum::randomEventCoolDown] = 1;
	delta[AttributeEnum::top_of_physical_quality] = -10;
	delta[AttributeEnum::physical_quality] = -10;
    delta[AttributeEnum::is_physical_ill] = 1;
	return delta;
}


