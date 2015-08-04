#ifndef DIRECTORIES_HPP
#define DIRECTORIES_HPP

#include <unordered_set>
#include "directory.hpp"

/** A container of directories **/
class Directories {
private:
    std::unordered_set<Directory> directories;

public:
    void load(const Directory& directory);
    auto begin() const { return directories.begin(); }
    auto end() const { return directories.end(); }
};


#endif //DIRECTORIES_HPP
