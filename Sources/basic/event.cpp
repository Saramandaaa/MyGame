#include "Headers/basic/event.h"

std::string Event::getText() const {
    return this->text;
}

void Event::changeText(const std::string& t) {
    this->text = t;
}

void Event::changeWeight(const double weight) {
    this->weight = weight;
}

attr Event::getDelta(const Character*, const int, std::string&) const {
    attr res;
    return res;
}

double Event::getWeight(const Character*) const {
    return weight;
}

bool Event::comparePriority(Event* first, Event* second) const {
    if (first->priority <= second->priority) return true;
    else return false;
}

Event::~Event() {
    std::string().swap(this->text);
}

attr TestEvent::getDelta(const Character*, const int option) const {
    attr res;
    res[AttributeEnum::physical_quality] = option + 1;
    return res;
}


std::string getEventName(int type) {
    switch (type) {
    case 0:
        return "BasicDailyEvent"; break;
    case 1:
        return "PrpDailyEvent"; break;
    case 2:
        return "InnovateDailyEvent"; break;
    case 5:
        return "EntranceExam"; break;
    case 3:
        return "MidTermExam"; break;
    case 4:
        return "FinalTermExam"; break;
    case 6:
        return "NewTerm"; break;
    case 7:
        return "Prp"; break;
    case 8:
        return "InnovateProgram"; break;
    case 9:
        return "JoinCorporation"; break;
    case 10:
        return "VoteStudentAssociation"; break;
    case 11:
        return "Love"; break;
    case 12:
        return "SayGoodBye"; break;
    case 13:
        return "PhysicalDisease"; break;
    case 14:
        return "MentalDisease"; break;
    case 15:
        return "Withdraw"; break;
    case 16:
        return "Baoyan"; break;
    case 17:
        return "Work"; break;
    case 18:
        return "PrpFinish"; break;
    case 19:
        return "InnovateFinish"; break;
    case 20:
        return "TotallyGoodbye"; break;
    }
    return "none";
}
