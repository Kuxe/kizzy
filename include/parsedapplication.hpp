#ifndef PARSEDAPPLICATION_HPP
#define PARSEDAPPLICATION_HPP

#include "application.hpp"

/** Used as return value from the parser **/
class ParsedApplication {
private:
    Application application;
    bool success;
public:
    ParsedApplication(const Application& application, bool success);

    //Will return trash if parsing failed
    const Application& get() const;

    //Check if parsing was ok or not ok (failed)
    bool ok() const;
};

#endif //PARSEDAPPLICATION_HPP
