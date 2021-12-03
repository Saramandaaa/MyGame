// 2021.12.3, 11:00. By ÌÆè÷ğ©, ´ó·ùÖØ¹¹. 

#include "attribute.h"

Attribute::Attribute() {
	isDelta = true;
	for (int i = 0; i < 8; i++) {
		attributes[i] = 0;
	}
}

Attribute::~Attribute() {

}

double& Attribute::operator[](int num) {
	return attributes[num];
}
double& Attribute::operator[](AttributeEnum attributeEnum) {
	return attributes[(int)attributeEnum];
}

void Attribute::print() {
	for (int i = 0; i < ATTR_AMT; i++) {
		printf("%6.2f ", attributes[i]);
	}
	printf("\n");
}