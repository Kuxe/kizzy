#include "searchstring.hpp"

void SearchString::add(const unsigned char& key) {
    str.push_back(key);
}

void SearchString::remove() {
	if(str.length() > 0) {
    	str.pop_back();
    }
}

void SearchString::clear() {
    str = "";
}

void SearchString::set(const std::string& str) {
    this->str = str;
}

const std::string& SearchString::get() const {
    return str;
}
