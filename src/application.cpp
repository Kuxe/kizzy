#include "application.hpp"

Application::Application(
    const std::string& name,
    const std::string& exec,
    const std::string& icon) :
    name(name), exec(exec), icon(icon) {

}

const std::string& Application::getName() const {
    return name;
}

const std::string& Application::getExec() const {
    return exec;
}

const std::string& Application::getIcon() const {
    return icon;
}
