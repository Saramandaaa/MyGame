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

	MentalDisease(const std::string& text);

	attr getDelta(const Character* character, const int option) const;

};

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

attr MentalDisease::mentalDiseaseContinue(const Character* character) const {
	attr delta;
    delta[AttributeEnum::bottom_of_pressure] = 10;
    delta[AttributeEnum::pressure] = 10;
	return delta;
}
