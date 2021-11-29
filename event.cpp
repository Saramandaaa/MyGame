#include"event.h"

std::string Event::getText() const  {
    return this->text;
}

attr Event::getDelta(const Character *user, const int option) const {
    attr res;
    return res;
}

Event::~Event() {
    std::string().swap(this->text);
}
