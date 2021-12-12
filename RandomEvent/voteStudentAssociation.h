#include<string>
#include<assert.h>

#include "attribute.h"
#include "character.h"
#include "event.h"

//触发概率=0.03;
//触发条件：无
//触发限制：每两学期仅出现一次
//学习效率=1;
class VoteStudentAssociation : public Event
{
	attr voteStudentAssociationJoin(const Character* character) const;
	attr voteStudentAssociationNotJoin(const Character* character) const;
public:
	VoteStudentAssociation();
	VoteStudentAssociation(const std::string& text);

	attr getDelta(const Character* character, const int option) const;

	double getWeight(const Character* character) const;

};

VoteStudentAssociation::VoteStudentAssociation() :
	VoteStudentAssociation("光荣志愿者")
{

}

VoteStudentAssociation::VoteStudentAssociation(const std::string& text) {
    type = EventEnum::VoteStudentAssociation;
	changeText(text);

	optionSet.insertOption(0, "参加");
	optionSet.insertOption(1, "不参加");
}

attr VoteStudentAssociation::getDelta(const Character* character, const int option) const {
	attr result;
	if (option == 0) result = voteStudentAssociationJoin(character);
	else if (option == 1) result = voteStudentAssociationNotJoin(character);
	else assert(false);
	return result;
}

double VoteStudentAssociation::getWeight(const Character* character) const {
	if (character->getSingleAttribute(AttributeEnum::randomEventCoolDown)) return 0;
	if (character->getSingleAttribute(AttributeEnum::voteCoolDown)) return 0;
	return weight * 0.03;
}

attr VoteStudentAssociation::voteStudentAssociationJoin(const Character* character) const {
	attr delta;
	delta[AttributeEnum::randomEventCoolDown] = 1;
	delta[AttributeEnum::study_rate] = 100 - character->getSingleAttribute(AttributeEnum::study_rate);
	delta[AttributeEnum::voteCoolDown] = 2;
	return delta;
}

attr VoteStudentAssociation::voteStudentAssociationNotJoin(const Character*) const {
	attr delta;
	delta[AttributeEnum::voteCoolDown] = 2;
	return delta;
}
