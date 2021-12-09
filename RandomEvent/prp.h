#include<string>
#include<assert.h>

#include "attribute.h"
#include "Character.h"
#include "event.h"

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
	Prp(const std::string& text);

	attr getDelta(const Character* character, const int option) const;


};

Prp::Prp(const std::string& text) {
	changeText(text);

	optionSet.insertOption(0, "参加");
	optionSet.insertOption(1, "不参加");
}

attr Prp::getDelta(const Character* character, const int option) const {
	attr result;
	if (option == 0) result = prpJoin(character);
	else if (option == 1) result = prpNotJoin(character);
	else assert(false);
	return result;
}

attr Prp::prpJoin(const Character* character) const {
	attr delta;
	delta[AttributeEnum::bottom_of_pressure] = 0.2;
	delta[AttributeEnum::is_of_prp] = 1;
	return delta;
}

attr Prp::prpNotJoin(const Character* character) const {
	attr delta;
	return delta;
}