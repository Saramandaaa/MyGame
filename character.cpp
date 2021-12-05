// 2021.12.3, 11:00. By �����, ����ع�. 
#include "character.h"
#include <assert.h>

Character::Character() {
    attribute.isDelta = false;
}
Character::~Character() {

}

attr Character::getAttributes() {
    return attribute;
}
/*int Character::getSingleAttribute(int id) {
    if (id < 0 || id > ATTR_AMT) return nullptr;
    return &(attributes[id]);
}*/
ATTR_TYPE Character::getSingleAttribute(AttributeEnum name) {
    int id = (int)name;
    assert (id >= 0 && id < ATTR_AMT);
    return attribute[name];
}

Character* Character::update(const attr& delta) {
    attribute += delta;
    return this;
}
/*double* Character::updateSingle(int id, double value, bool isDelta) {
    if (id < 0 || id >= ATTR_AMT) return nullptr;
    if (isDelta) attributes[id] += value;
    else attributes[id] = value;
    return &(attributes[id]);
}*/
ATTR_TYPE Character::updateSingle(AttributeEnum name, ATTR_TYPE value, bool isDelta) {
    int id = (int)name;
    assert(id >= 0 && id < ATTR_AMT);
    if (isDelta) attribute[name] += value;
    else attribute[name] = value;
    return attribute[name];
}
