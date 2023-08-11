#include "../include/directory.hpp"
#include <dirent.h>
#include "../include/desktopparser.hpp"

Directory::Directory(const std::string& path) :
    path(path) {

    DIR* directory;
    struct dirent* entry;

    //Open directory
    if((directory = opendir(path.c_str())) != NULL) {

        //While there are still entries in the directory
        while((entry = readdir(directory)) != NULL) {
            //Try to parse the entry into an application
            const ParsedApplication& parsedApplication = DesktopParser::parse(path + entry->d_name);
            if(parsedApplication.ok()) {
                applications.insert(parsedApplication.get());
            }
        }

        //No entries left - close the directory
        closedir(directory);
    }
}

bool Directory::operator==(const Directory& rhs) const {
    return path.compare(rhs.path) == 0;
}
