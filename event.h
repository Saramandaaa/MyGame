// Update at 11/30, 22:50. By ÌÆè÷ð©, Ìí¼ÓOptionSet. 

#ifndef EVENT_H
#define EVENT_H

#include <vector>
#include <string>
#include "character.h"
#include "optionset.h"

class Event {
public:
    virtual attr getDelta(const Character*, const int) const;
    std::string getText(void) const;
    virtual ~Event();
    Event() {};
    Event(const std::string& t) : text(t) {};
    OptionSet optionSet;
private:
    std::string text;
};

#endif // EVENT_H
