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
	VoteStudentAssociation(const std::string& text);

	attr getDelta(const Character* character, const int option) const;


};

VoteStudentAssociation::VoteStudentAssociation(const std::string& text) {
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

attr VoteStudentAssociation::voteStudentAssociationJoin(const Character* character) const {
	attr delta;
	delta[AttributeEnum::study_rate] = 100;
	return delta;
}

attr VoteStudentAssociation::voteStudentAssociationNotJoin(const Character* character) const {
	attr delta;
	return delta;
}