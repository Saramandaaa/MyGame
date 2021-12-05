// Update at 11/30, 22:50. By ÌÆè÷ð©, Ìí¼ÓOptionSet
#include"event.h"

std::string Event::getText() const {
    return this->text;
}

void Event::changeText(const std::string& t) {
    this->text = t;
}

attr Event::getDelta(const Character* user, const int option) const {
    attr res;
    return res;
}

Event::~Event() {
    std::string().swap(this->text);
}

attr TestEvent::getDelta(const Character* user, const int option) const {
    attr res;
    res[AttributeEnum::physical_quality] = option;
    return res;
}
