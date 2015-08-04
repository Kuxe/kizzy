#ifndef DIRECTORY_HPP
#define DIRECTORY_HPP

#include <string>
#include "applications.hpp"

/** Represents an directory with .desktop files **/
class Directory {
private:
    friend std::hash<Directory>;
    
    const std::string path;
    Applications applications;

public:
    Directory(const std::string& path);
    bool operator==(const Directory& rhs) const;
    auto begin() const { return applications.begin(); }
    auto end() const { return applications.end(); }

};

namespace std {
    template<>
    struct hash<Directory> {
        std::size_t operator()(Directory const& dir) const {
            return std::hash<std::string>()(dir.path) ;
        }
    };
}


#endif //DIRECTORY_HPP
