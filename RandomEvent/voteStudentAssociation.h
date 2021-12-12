#include<string>
#include<assert.h>

#include "attribute.h"
#include "character.h"
#include "event.h"

//��������=0.03;
//������������
//�������ƣ�ÿ��ѧ�ڽ�����һ��
//ѧϰЧ��=1;
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
	VoteStudentAssociation("����־Ը��")
{

}

VoteStudentAssociation::VoteStudentAssociation(const std::string& text) {
    type = EventEnum::VoteStudentAssociation;
	changeText(text);

	optionSet.insertOption(0, "�μ�");
	optionSet.insertOption(1, "���μ�");
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
