// Updata at 11/30, 22:50. By ÌÆè÷ð©, ³õ´Î±àÐ´. 

#include "optionset.h"

OptionSet::OptionSet() {

}

OptionSet::~OptionSet() {

}

bool OptionSet::insertOption(int id, std::string description) {
	for (std::vector<std::pair<int, std::string>>::iterator it = optionSet.begin(); it != optionSet.end(); it++) {
		if (it->first == id) return false;
		if (it->first > id) {
			optionSet.insert(it, make_pair(id, description));
			return true;
		}
	}
	optionSet.insert(optionSet.end(), make_pair(id, description));
	return true;
}

bool OptionSet::removeOption(int id) {
	for (std::vector<std::pair<int, std::string>>::iterator it = optionSet.begin(); it != optionSet.end(); it++) {
		if (it->first == id) {
			optionSet.erase(it);
			return true;
		}
	}
	return false;
}

std::pair<int, std::string>* OptionSet::findOption(int id) {
	for (std::vector<std::pair<int, std::string>>::iterator it = optionSet.begin(); it != optionSet.end(); it++) {
		if (it->first == id) return &*it;
	}
	return nullptr;
}

void OptionSet::clearOption() {
	optionSet.clear();
}

void OptionSet::traverse() {
	for (std::vector<std::pair<int, std::string>>::iterator it = optionSet.begin(); it != optionSet.end(); it++) {
		printf("%d, %s. \n", it->first, it->second.c_str());
	}
}

int OptionSet::size() {
    return optionSet.size();
}
