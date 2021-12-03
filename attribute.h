// 2021.12.3, 11:00. By 唐梓皓, 大幅重构. 

#ifndef _ATTRIBUTE_H_
#define _ATTRIBUTE_H_
#include<stdio.h>

// 定义了double类属性的数量
#define ATTR_AMT 8

// 定义了double类属性的id，请务必与ATTR_AMT同步更新，建议在枚举类型后指明对应的int数
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
    
    // 可用中括号直接访问元素，可使用id或属性（须用AttributeEnum作为命名空间，如AttributeEnum::basicStrength）
    // 没有溢出保护
    double& operator[](int num);
    double& operator[](AttributeEnum attributeEnum);

    void print(); // 仅限测试用
    
};



#endif

