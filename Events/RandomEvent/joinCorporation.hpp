#include<string>
#include<assert.h>

#include "Headers/basicheader.h"

//��������=0.5+�罻��*0.1;
//�������������ڵ�һѧ�����к�ĵ�һ���ճ��¼�
//ѧϰЧ��=1;
class JoinCorporation : public Event
{
	attr joinCorporationJoin(const Character* character) const;
	attr joinCorporationNotJoin(const Character* character) const;

public:
	JoinCorporation();
	JoinCorporation(const std::string& text);

    attr getDelta(const Character* character, const int option, std::string&) const;
	double getWeight(const Character* character) const;
};

JoinCorporation::JoinCorporation() :
    JoinCorporation("�Ƿ�������Ż������֮���ճ��¼������ֻ��Ӱ�콫����")
{

}

JoinCorporation::JoinCorporation(const std::string& text) {
    type = EventEnum::JoinCorporation;
	changeText(text);
	optionSet.insertOption(0, "����");
	optionSet.insertOption(1, "������");
}

attr JoinCorporation::getDelta(const Character* character, const int option, std::string&) const {
	attr result;
	if (option == 0) result = joinCorporationJoin(character);
	else if (option == 1) result = joinCorporationNotJoin(character);
	else assert(false);
	return result;
}

double JoinCorporation::getWeight(const Character* character) const {
	if (character->getSingleAttribute(AttributeEnum::randomEventCoolDown)) return 0;
    if (character->getSingleAttribute(AttributeEnum::day) % 20 != 11) return 0;
    //double weight = (0.5 + character->getSingleAttribute(AttributeEnum::social) * 0.001) * this->weight;
    //return weight;
    return -1;
}

attr JoinCorporation::joinCorporationJoin(const Character*) const {
	attr delta;
	delta[AttributeEnum::randomEventCoolDown] = 1;
    delta[AttributeEnum::study_rate] = 100;
	return delta;
}
attr JoinCorporation::joinCorporationNotJoin(const Character*) const {
	attr delta;
	delta[AttributeEnum::randomEventCoolDown] = 1;
	return delta;
}
