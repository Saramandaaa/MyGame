// 2021.12.6, 19:23. By Saramanda

#ifndef _ATTRIBUTE_H_
#define _ATTRIBUTE_H_
#include <cstdio>

// ������double�����Ե�����
#define ATTR_AMT ((int)AttributeEnum::attribute_end)
typedef int ATTR_TYPE; //������Եı�������

// ������double�����Ե�id���������ATTR_AMTͬ�����£�������ö�����ͺ�ָ����Ӧ��int��
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
    double physical_quality;              //�������ʣ��ɼ�)   ��������<������-���ޣ�*0.2 ����
    double top_of_physical_quality=1;     //�����������ޣ��ǿɼ���
    double pressure;                      //ѹ�����ɼ���      ѹ��>������-���ޣ�*0.8+���� ����
    double bottom_of_pressure=0;          //ѹ������(�ǿɼ�)
    double study_rate;                    //ѧϰЧ�ʣ��ǿɼ���
    double top_of_study_rate=1;           //ѧϰЧ�����ޣ��ǿɼ���
    double knowledge;                     //��ѧ��֪ʶˮƽ���ɼ���
    double all_knowledge=0;               //��ѧ��֪ʶˮƽ���ɼ���
    double scientific_research_time=0;    //���о���(�ɼ�)
    double social=0;                      //�罻��(�ǿɼ�)
    int    term=1;                        //��ǰѧ������1-8�����ɼ���
    char   affair5[5];                    //��5���¼���¼(�ɼ�)
    bool   is_of_prp=0;                   //�Ƿ�μ�prp���ǿɼ���
    bool   is_of_love=0;                  //�Ƿ��������ǿɼ���
    bool   is_of_novation=0;              //�Ƿ�μӴ󴴣��ǿɼ���
    int    number_love=0;                 //�����������ǿɼ���
    int    time_love=0;                   //�����������ɼ���
    int    number_prp=0;                  //prp_task�������ɼ���
    int    number_novation=0;             //novation_taks�������ɼ���*/


class Attribute
{
	
public:
    bool isDelta;
    ATTR_TYPE attributes[ATTR_AMT];
	
    Attribute();
	~Attribute();
    
    // ����������ֱ�ӷ���Ԫ�أ���ʹ��id�����ԣ�����AttributeEnum��Ϊ�����ռ䣬��AttributeEnum::basicStrength��
    // û���������
    ATTR_TYPE& operator[](const AttributeEnum attributeEnum);
    void operator+=(Attribute other); //other��isDelta����Ϊtrue���򱨴�
    void print(); // ���޲�����
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

