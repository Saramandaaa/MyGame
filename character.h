#ifndef CHARACTER_H
#define CHARACTER_H

#include <vector>

typedef std::vector<int> attr;

class Character {
public:
    Character* update(const attr&);
private:

};

#endif // CHARACTER_H
