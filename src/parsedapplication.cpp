#include "parsedapplication.hpp"

ParsedApplication::ParsedApplication(const Application& application, bool success) :
    application(application), success(success) {

};

const Application& ParsedApplication::get() const {
    return application;
}

bool ParsedApplication::ok() const {
    return success;
}
