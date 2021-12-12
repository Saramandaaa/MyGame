// 2021.12.6, 19:23. By Saramanda

#ifndef CHARACTER_H
#define CHARACTER_H

#include <vector>

#include "Headers/basic/attribute.h"

typedef Attribute attr;

class Character {
public:
    //初始属性全为0
    Character();
    Character(attr);
    ~Character();

    // 以attr的类型输出角色属性
    attr getAttributes() const;
    // 以ATTR_TYPE的类型输出角色的单个属性, 查找失败则报错
    ATTR_TYPE getSingleAttribute(AttributeEnum name) const;

    // 该函数可以一次性调整attr中包含的属性，参数的isDelta必须为true
    Character* update(const attr&);
    // 该函数可以更新单个属性，须以AttributeEnum为命名空间，如AttributeEnum::physical_quality
    // isDelta表示value是变化量还是直接赋值
    ATTR_TYPE updateSingle(AttributeEnum name, ATTR_TYPE value, bool isDelta);
    
    // 仅限测试用
    //void printAttribute();
private:
    attr attribute;
};

#endif // CHARACTER_H
