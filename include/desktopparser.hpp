#ifndef DESKTOPPARSER_HPP
#define DESKTOPPARSER_HPP

#include "parsedapplication.hpp"

/** Class for parsing .desktop-files **/
class DesktopParser {
private:
public:
    static const ParsedApplication parse(const std::string& filePath);
};

#endif //DESKTOPPARSER_HPP
