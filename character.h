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
    //int getSingleAttribute(int id);
    ATTR_TYPE getSingleAttribute(AttributeEnum name);

    // �ú�������һ���Ե���attr�а��������ԣ��������Ե�isDelta����attr�е���ͬ
    Character* update(const attr&);
    // �ú������Ը��µ������ԣ�����id��������������AttributeEnumΪ�����ռ䣬��AttributeEnum::basicStrength��ѡ������
    // ������û��basic��final���Ե�������������������ʱȷ����ȷ
    // �������ʧ�ܵ��¸���ʧ�ܣ��᷵�ؿ�ָ��nullptr
    //double* updateSingle(int id, double value, bool isDelta);
    ATTR_TYPE updateSingle(AttributeEnum name, ATTR_TYPE value, bool isDelta);
    
    // ���޲�����
    //void printAttribute();
private:
    attr attribute;
};

#endif // CHARACTER_H
