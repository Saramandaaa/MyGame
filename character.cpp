// 2021.12.3, 11:00. By ÌÆè÷ğ©, ´ó·ùÖØ¹¹. 
#include "character.h"
#include <assert.h>

Character::Character() {
    attribute.isDelta = false;
    attribute[AttributeEnum::physical_quality] = 100;
    attribute[AttributeEnum::top_of_physical_quality] = 100;
    attribute[AttributeEnum::study_rate] = 100;
    attribute[AttributeEnum::top_of_study_rate] = 100;
    attribute[AttributeEnum::term] = 1;
    attribute[AttributeEnum::affair0] = -1;
    attribute[AttributeEnum::affair1] = -1;
    attribute[AttributeEnum::affair2] = -1;
    attribute[AttributeEnum::affair3] = -1;
    attribute[AttributeEnum::affair4] = -1;
}
Character::~Character() {

}

attr Character::getAttributes() const {
    return attribute;
}

ATTR_TYPE Character::getSingleAttribute(AttributeEnum name) const {
    int id = (int)name;
    assert (id >= 0 && id < ATTR_AMT);
    return attribute.attributes[(int)name];
}

Character* Character::update(const attr& delta) {
    attribute += delta;
    return this;
}

ATTR_TYPE Character::updateSingle(AttributeEnum name, ATTR_TYPE value, bool isDelta) {
    int id = (int)name;
    assert(id >= 0 && id < ATTR_AMT);
    if (isDelta) attribute[name] += value;
    else attribute[name] = value;
    return attribute[name];
}
