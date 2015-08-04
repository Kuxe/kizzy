#ifndef SEARCHSTRING_HPP
#define SEARCHSTRING_HPP

#include <string>

/** Represents the current string used for searching **/
class SearchString {
private:
    std::string str;
public:
    void add(const unsigned char& key);
    void remove();
    void clear();
    void set(const std::string& str);
    const std::string& get() const;
};

#endif //SEARCHSTRINH_HPP
