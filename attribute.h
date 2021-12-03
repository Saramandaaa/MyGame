// 2021.12.3, 11:00. By �����, ����ع�. 

#ifndef _ATTRIBUTE_H_
#define _ATTRIBUTE_H_
#include<stdio.h>

// ������double�����Ե�����
#define ATTR_AMT 8

// ������double�����Ե�id���������ATTR_AMTͬ�����£�������ö�����ͺ�ָ����Ӧ��int��
enum class AttributeEnum
{
    basicStrength = 0,
    finalStrength = 1,
    basicIntelligence = 2,
    finalIntelligence = 3,
    basicStress = 4,
    finalStress = 5,
    basicSocialAbility = 6,
    finalSocialAbility = 7
};


class Attribute
{
	
public:
	bool isDelta;
    double attributes[ATTR_AMT];
	
    Attribute();
	~Attribute();
    
    // ����������ֱ�ӷ���Ԫ�أ���ʹ��id�����ԣ�����AttributeEnum��Ϊ�����ռ䣬��AttributeEnum::basicStrength��
    // û���������
    double& operator[](int num);
    double& operator[](AttributeEnum attributeEnum);

    void print(); // ���޲�����
    
};



#endif

