// Update at 11/30, 22:50. By �����, ����OptionSet
#include"event.h"

std::string Event::getText() const {
    return this->text;
}

void Event::changeText(const std::string& t) {
    this->text = t;
}

attr Event::getDelta(const Character*, const int) const {
    attr res;
    return res;
}

Event::~Event() {
    std::string().swap(this->text);
}

attr TestEvent::getDelta(const Character*, const int option) const {
    attr res;
    res[AttributeEnum::physical_quality] = option + 1;
    return res;
}
