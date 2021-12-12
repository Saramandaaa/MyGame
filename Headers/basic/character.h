// 2021.12.6, 19:23. By Saramanda

#ifndef CHARACTER_H
#define CHARACTER_H

#include <vector>

#include "Headers/basic/attribute.h"

typedef Attribute attr;

class Character {
public:
    //��ʼ����ȫΪ0
    Character();
    Character(attr);
    ~Character();

    // ��attr�����������ɫ����
    attr getAttributes() const;
    // ��ATTR_TYPE�����������ɫ�ĵ�������, ����ʧ���򱨴�
    ATTR_TYPE getSingleAttribute(AttributeEnum name) const;

    // �ú�������һ���Ե���attr�а��������ԣ�������isDelta����Ϊtrue
    Character* update(const attr&);
    // �ú������Ը��µ������ԣ�����AttributeEnumΪ�����ռ䣬��AttributeEnum::physical_quality
    // isDelta��ʾvalue�Ǳ仯������ֱ�Ӹ�ֵ
    ATTR_TYPE updateSingle(AttributeEnum name, ATTR_TYPE value, bool isDelta);
    
    // ���޲�����
    //void printAttribute();
private:
    attr attribute;
};

#endif // CHARACTER_H
