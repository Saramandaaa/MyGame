// 2021.12.3, 11:00. By �����, ����ع�. 

#ifndef CHARACTER_H
#define CHARACTER_H

#include <vector>

#include "attribute.h"

typedef Attribute attr;

class Character {
public:
    //��ʼ����ȫΪ0
    Character();
    ~Character();


    // ��attr�����������ɫ����
    attr getAttributes();
    // ��double*�����������ɫ�ĵ�������, ����ʧ���򷵻ؿ�ָ��nullptr
    double* getSingleAttribute(int id);
    double* getSingleAttribute(AttributeEnum name);

    // �ú�������һ���Ե���attr�а��������ԣ��������Ե�isDelta����attr�е���ͬ
    Character* update(attr&);
    // �ú������Ը��µ������ԣ�����id��������������AttributeEnumΪ�����ռ䣬��AttributeEnum::basicStrength��ѡ������
    // ������û��basic��final���Ե�������������������ʱȷ����ȷ
    // �������ʧ�ܵ��¸���ʧ�ܣ��᷵�ؿ�ָ��nullptr
    double* updateSingle(int id, double value, bool isDelta);
    double* updateSingle(AttributeEnum name, double value, bool isDelta);
    

    // ���޲�����
    void printAttribute(); 
private:
    double attributes[ATTR_AMT];
    
};

#endif // CHARACTER_H
