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
	VoteStudentAssociation(const std::string& text);

	attr getDelta(const Character* character, const int option) const;


};

VoteStudentAssociation::VoteStudentAssociation(const std::string& text) {
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

attr VoteStudentAssociation::voteStudentAssociationJoin(const Character* character) const {
	attr delta;
	delta[AttributeEnum::study_rate] = 100;
	return delta;
}

attr VoteStudentAssociation::voteStudentAssociationNotJoin(const Character* character) const {
	attr delta;
	return delta;
}