// 2021.12.3, 11:00. By 唐梓皓, 大幅重构. 

#ifndef CHARACTER_H
#define CHARACTER_H

#include <vector>

#include "attribute.h"

typedef Attribute attr;

class Character {
public:
    //初始属性全为0
    Character();
    ~Character();


    // 以attr的类型输出角色属性
    attr getAttributes();
    // 以double*的类型输出角色的单个属性, 查找失败则返回空指针nullptr
    double* getSingleAttribute(int id);
    double* getSingleAttribute(AttributeEnum name);

    // 该函数可以一次性调整attr中包含的属性，但各属性的isDelta都与attr中的相同
    Character* update(attr&);
    // 该函数可以更新单个属性，可用id或属性名（须以AttributeEnum为命名空间，如AttributeEnum::basicStrength）选定属性
    // 本函数没有basic和final属性的联动，请在数据输入时确保正确
    // 如因查找失败导致更新失败，会返回空指针nullptr
    double* updateSingle(int id, double value, bool isDelta);
    double* updateSingle(AttributeEnum name, double value, bool isDelta);
    

    // 仅限测试用
    void printAttribute(); 
private:
    double attributes[ATTR_AMT];
    
};

#endif // CHARACTER_H
