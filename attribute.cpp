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
int& Attribute::operator[](AttributeEnum attributeEnum) {
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
