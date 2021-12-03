// 2021.12.3, 11:00. By ÌÆè÷ð©, ´ó·ùÖØ¹¹. 
#include"character.h"

Character::Character() {
    for (int i = 0; i < ATTR_AMT; i++) {
        attributes[i] = 0;
    }
}
Character::~Character() {

}

attr Character::getAttributes() {
    Attribute attribute;
    for (int i = 0; i < ATTR_AMT; i++) {
        attribute[i] = attributes[i];
    }
    return attribute;
}
double* Character::getSingleAttribute(int id) {
    if (id < 0 || id > ATTR_AMT) return nullptr;
    return &(attributes[id]);
}
double* Character::getSingleAttribute(AttributeEnum name) {
    int id = (int)name;
    if (id < 0 || id > ATTR_AMT) return nullptr;
    return &(attributes[id]);
}

Character* Character::update(attr& attribute) {
    for (int i = 0; i < ATTR_AMT; i++) {
        updateSingle((AttributeEnum)i, attribute[i], attribute.isDelta);
    }
    return this;
}
double* Character::updateSingle(int id, double value, bool isDelta) {
    if (id < 0 || id >= ATTR_AMT) return nullptr;
    if (isDelta) attributes[id] += value;
    else attributes[id] = value;
    return &(attributes[id]);
}
double* Character::updateSingle(AttributeEnum name, double value, bool isDelta) {
    int id = (int)name;
    if (id < 0 || id >= ATTR_AMT) return nullptr;
    if (isDelta) attributes[id] += value;
    else attributes[id] = value;
    return &(attributes[id]);
}

void Character::printAttribute() {
    for (int i = 0; i < ATTR_AMT; i++) {
        printf("%6.2f ", attributes[i]);
    }
    printf("\n");
}
