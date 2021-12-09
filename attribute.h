// 2021.12.6, 19:23. By Saramanda

#ifndef _ATTRIBUTE_H_
#define _ATTRIBUTE_H_
#include <cstdio>

// 定义了double类属性的数量
#define ATTR_AMT ((int)AttributeEnum::attribute_end)
typedef int ATTR_TYPE; //存放属性的变量类型

// 定义了double类属性的id，请务必与ATTR_AMT同步更新，建议在枚举类型后指明对应的int数
enum class AttributeEnum
{
    affair0 = 0,
    affair1 = 1,
    affair2 = 2,
    affair3 = 3,
    affair4 = 4,
    physical_quality = 5,
    top_of_physical_quality = 6,
    pressure = 7,
    bottom_of_pressure = 8,
    study_rate = 9,
    top_of_study_rate = 10,
    knowledge = 11,
    all_knowledge = 12,
    scientific_research_time = 13,
    social = 14,
    term = 15,
    is_of_prp = 16,
    is_of_love = 17,
    is_of_novation = 18,
    number_love = 19,
    time_love = 20,
    number_prp = 21,
    number_novation = 22,
    failedCourseAmt = 23,
    attribute_end
};
/*
    double physical_quality;              //身体素质（可见)   身体素质<（上限-下限）*0.2 报警
    double top_of_physical_quality=1;     //身体素质上限（非可见）
    double pressure;                      //压力（可见）      压力>（上限-下限）*0.8+下限 报警
    double bottom_of_pressure=0;          //压力下限(非可见)
    double study_rate;                    //学习效率（非可见）
    double top_of_study_rate=1;           //学习效率上限（非可见）
    double knowledge;                     //本学期知识水平（可见）
    double all_knowledge=0;               //总学期知识水平（可见）
    double scientific_research_time=0;    //科研经验(可见)
    double social=0;                      //社交力(非可见)
    int    term=1;                        //当前学期数（1-8）（可见）
    char   affair5[5];                    //近5次事件记录(可见)
    bool   is_of_prp=0;                   //是否参加prp（非可见）
    bool   is_of_love=0;                  //是否恋爱（非可见）
    bool   is_of_novation=0;              //是否参加大创（非可见）
    int    number_love=0;                 //恋爱次数（非可见）
    int    time_love=0;                   //恋爱天数（可见）
    int    number_prp=0;                  //prp_task次数（可见）
    int    number_novation=0;             //novation_taks次数（可见）*/


class Attribute
{
	
public:
    bool isDelta;
    ATTR_TYPE attributes[ATTR_AMT];
	
    Attribute();
	~Attribute();
    
    // 可用中括号直接访问元素，可使用id或属性（须用AttributeEnum作为命名空间，如AttributeEnum::basicStrength）
    // 没有溢出保护
    ATTR_TYPE& operator[](const AttributeEnum attributeEnum);
    void operator+=(Attribute other); //other的isDelta必须为true否则报错
    void print(); // 仅限测试用
    int getStudy();
    int getExercise();
    int getEntertainment();
    int getPrp();
    int getNovation();
    int getTask();

private:
    ATTR_TYPE& operator[](int num);
    
};

#endif

