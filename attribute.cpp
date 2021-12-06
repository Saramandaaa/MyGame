// 2021.12.3, 11:00. By ÌÆè÷ð©, ´ó·ùÖØ¹¹. 

#include "attribute.h"
#include <assert.h>
#include <QDebug>

Attribute::Attribute() {
	isDelta = true;
    for (int i = 0; i < ATTR_AMT; i++) {
		attributes[i] = 0;
	}
}

Attribute::~Attribute() {

}

int& Attribute::operator[](int num) {
	return attributes[num];
}
int& Attribute::operator[](const AttributeEnum attributeEnum) {
	return attributes[(int)attributeEnum];
}
void Attribute::operator+=(Attribute other) {
    assert(other.isDelta);
    for (int i = 0; i < 18; i++) {
        attributes[i] += other[i];
    }
    for (int i = 18; i < ATTR_AMT; i++) {
        attributes[i] = other[i];
    }
}

void Attribute::print() {
	for (int i = 0; i < ATTR_AMT; i++) {
        qDebug() << attributes[i];
	}
    //printf("\n");
}

int Attribute::getStudy() {
    int result = 0;
    result += (attributes[(int)AttributeEnum::affair0] == 0);
    result += (attributes[(int)AttributeEnum::affair1] == 0);
    result += (attributes[(int)AttributeEnum::affair2] == 0);
    result += (attributes[(int)AttributeEnum::affair3] == 0);
    result += (attributes[(int)AttributeEnum::affair4] == 0);
    return result;
}
int Attribute::getExercise() {
    int result = 0;
    result += (attributes[(int)AttributeEnum::affair0] == 1);
    result += (attributes[(int)AttributeEnum::affair1] == 1);
    result += (attributes[(int)AttributeEnum::affair2] == 1);
    result += (attributes[(int)AttributeEnum::affair3] == 1);
    result += (attributes[(int)AttributeEnum::affair4] == 1);
    return result;
}
int Attribute::getEntertainment() {
    int result = 0;
    result += (attributes[(int)AttributeEnum::affair0] == 2);
    result += (attributes[(int)AttributeEnum::affair1] == 2);
    result += (attributes[(int)AttributeEnum::affair2] == 2);
    result += (attributes[(int)AttributeEnum::affair3] == 2);
    result += (attributes[(int)AttributeEnum::affair4] == 2);
    return result;
}
int Attribute::getPrp() {
    int result = 0;
    result += (attributes[(int)AttributeEnum::affair0] == 3);
    result += (attributes[(int)AttributeEnum::affair1] == 3);
    result += (attributes[(int)AttributeEnum::affair2] == 3);
    result += (attributes[(int)AttributeEnum::affair3] == 3);
    result += (attributes[(int)AttributeEnum::affair4] == 3);
    return result;
}
int Attribute::getNovation() {
    int result = 0;
    result += (attributes[(int)AttributeEnum::affair0] == 4);
    result += (attributes[(int)AttributeEnum::affair1] == 4);
    result += (attributes[(int)AttributeEnum::affair2] == 4);
    result += (attributes[(int)AttributeEnum::affair3] == 4);
    result += (attributes[(int)AttributeEnum::affair4] == 4);
    return result;
}
int Attribute::getTask() {
    return getPrp() + getNovation();
}
