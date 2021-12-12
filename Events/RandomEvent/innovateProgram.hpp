#include<string>
#include<assert.h>

#include "Headers/basicheader.h"

//触发条件：总知识水平能力>=85(当前学期数-1)、每个学期（第一学期除外）开始
//开启daily_event_novationtask，限时三个学期
//压力下限+0.3（完成时归0）
//完成条件：完成13次daily_event_novationtask
//完成奖励：科研经历+2；总知识水平能力delta=完成daily_event_prptask次数*6
//注：prp与innovate_program不共存
class InnovateProgram : public Event
{
	attr innovateProgramJoin(const Character* character) const;
	attr innovateProgramNotJoin(const Character* character) const;

public:
	InnovateProgram();
	InnovateProgram(const std::string& text);

    attr getDelta(const Character* character, const int option, std::string&) const;
	double getWeight(const Character* character) const;
	
};

InnovateProgram::InnovateProgram() :
    InnovateProgram("是否加入大创项目？加入后，需要在3个学期内进行至少9次大创活动以通过答辩。完成后将获得科研和知识奖励。")
{

}

InnovateProgram::InnovateProgram(const std::string& text) {
    type = EventEnum::InnovateProgram;
	changeText(text);
	optionSet.insertOption(0, "参加");
	optionSet.insertOption(1, "不参加");
}

attr InnovateProgram::getDelta(const Character* character, const int option, std::string&) const {
	attr result;
	if (option == 0) result = innovateProgramJoin(character);
	else if (option == 1) result = innovateProgramNotJoin(character);
	else assert(false);
	return result;
}

double InnovateProgram::getWeight(const Character* character) const {
	if (character->getSingleAttribute(AttributeEnum::randomEventCoolDown)) return 0;
    if (character->getSingleAttribute(AttributeEnum::is_of_prp)) return 0;
	if (character->getSingleAttribute(AttributeEnum::is_of_novation)) return 0;
    if (character->getSingleAttribute(AttributeEnum::term) == 1 || character->getSingleAttribute(AttributeEnum::term) > 5) return 0;
	if (character->getSingleAttribute(AttributeEnum::all_knowledge) < 85 * character->getSingleAttribute(AttributeEnum::term) - 85) return 0;
    return weight;
}

attr InnovateProgram::innovateProgramJoin(const Character*) const {
	attr delta;
	delta[AttributeEnum::randomEventCoolDown] = 1;
	delta[AttributeEnum::is_of_novation] = 1;
    delta[AttributeEnum::bottom_of_pressure] = 30;
	delta[AttributeEnum::innovate_term_remain] = 3;
	return delta;
}

attr InnovateProgram::innovateProgramNotJoin(const Character*) const {
	attr delta;
	delta[AttributeEnum::randomEventCoolDown] = 1;
	return delta;
}
