#include "../include/desktopparser.hpp"
#include <fstream>
#include <cstring>

const ParsedApplication DesktopParser::parse(const std::string& filePath) {
    std::string name = "UNSET", exec = "UNSET", icon = "UNSET";
    bool foundName = false, foundExec = false, foundIcon = false;

    std::ifstream file(filePath);

    //Check if opening was succesfull
    //Stop checking if file isnt open, if getline returns EOF
    //or if everything needed were found
    constexpr unsigned short BUFFER_SIZE = 512;
    char buffer[BUFFER_SIZE];
    while(
        file.is_open() &&
        file.getline(buffer, BUFFER_SIZE) &&
        !(foundName && foundExec && foundIcon)) {
        if(strstr(buffer, "Name=") && !foundName) {
            name = &buffer[5];
            foundName = true;
        } else if(strstr(buffer, "TryExec=") && !foundExec) {
            exec = &buffer[8];
            foundExec = true;
        } else if(strstr(buffer, "Exec=") && !foundExec) {
            exec = &buffer[5];
            foundExec = true;
        } else if(strstr(buffer, "Icon=") && !foundIcon) {
            icon = &buffer[5];
            foundIcon = true;
        }
    }

    //Always close filstream
    file.close();

    return ParsedApplication({name, exec, icon}, foundName && foundExec && foundIcon);
}
