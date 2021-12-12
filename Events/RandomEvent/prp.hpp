#include<string>
#include<assert.h>

#include "Headers/basicheader.h"

//触发条件：总知识水平能力>=80(当前学期数-1)、每个学期（第一学期除外）开始
//开启daily_event_prptask，限时两个学期
//压力下限+0.2（完成时归0）
//完成条件：完成8次daily_event_prptask
//完成奖励：科研经历+1；总知识水平能力delta=完成daily_event_prptask次数*4
//注：prp与innovate_program不共存

class Prp : public Event
{
	attr prpJoin(const Character* character) const;
	attr prpNotJoin(const Character* character) const;
public:
	Prp();
	Prp(const std::string& text);

    attr getDelta(const Character* character, const int option, std::string&) const;

	double getWeight(const Character* character) const;

};

Prp::Prp() :
    Prp("是否加入PRP项目？加入后，需要在2个学期内进行至少6次PRP活动以通过答辩。完成后将获得科研和知识奖励")
{

}

Prp::Prp(const std::string& text) {
    type = EventEnum::Prp;
	changeText(text);

	optionSet.insertOption(0, "参加");
	optionSet.insertOption(1, "不参加");
}

attr Prp::getDelta(const Character* character, const int option, std::string&) const {
	attr result;
	if (option == 0) result = prpJoin(character);
	else if (option == 1) result = prpNotJoin(character);
	else assert(false);
	return result;
}

double Prp::getWeight(const Character* character) const {
	if (character->getSingleAttribute(AttributeEnum::randomEventCoolDown)) return 0;
    if (character->getSingleAttribute(AttributeEnum::is_of_novation)) return 0;
	if (character->getSingleAttribute(AttributeEnum::is_of_prp)) return 0;
    if (character->getSingleAttribute(AttributeEnum::term) == 1 || character->getSingleAttribute(AttributeEnum::term) > 6) return 0;
	if (character->getSingleAttribute(AttributeEnum::all_knowledge) < 80 * character->getSingleAttribute(AttributeEnum::term) - 80) return 0;
	return weight;
}

attr Prp::prpJoin(const Character*) const {
	attr delta;
	delta[AttributeEnum::randomEventCoolDown] = 1;
    delta[AttributeEnum::bottom_of_pressure] = 20;
	delta[AttributeEnum::is_of_prp] = 1;
	delta[AttributeEnum::prp_term_remain] = 2;
	return delta;
}

attr Prp::prpNotJoin(const Character*) const {
	attr delta;
	delta[AttributeEnum::randomEventCoolDown] = 1;
	return delta;
}
