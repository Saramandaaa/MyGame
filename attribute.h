// 2021.12.6, 19:23. By Saramanda

#ifndef _ATTRIBUTE_H_
#define _ATTRIBUTE_H_
#include <cstdio>

// ������double�����Ե�����
#define ATTR_AMT 23
typedef int ATTR_TYPE; //������Եı�������

// ������double�����Ե�id���������ATTR_AMTͬ�����£�������ö�����ͺ�ָ����Ӧ��int��
enum class AttributeEnum
{
    physical_quality = 0,
    top_of_physical_quality = 1,
    pressure = 2,
    bottom_of_pressure = 3,
    study_rate = 4,
    top_of_study_rate = 5,
    knowledge = 6,
    all_knowledge = 7,
    scientific_research_time = 8,
    social = 9,
    term = 10,
    is_of_prp = 11,
    is_of_love = 12,
    is_of_novation = 13,
    number_love = 14,
    time_love = 15,
    number_prp = 16,
    number_novation = 17,
    affair0 = 18,
    affair1 = 19,
    affair2 = 20,
    affair3 = 21,
    affair4 = 22,
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

