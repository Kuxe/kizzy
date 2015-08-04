#ifndef APPLICATIONS_HPP
#define APPLICATIONS_HPP

#include <unordered_set>
#include "application.hpp"

/** A container of Applications **/
class Applications {
private:
    std::unordered_set<Application> applications;
public:
    void insert(const Application& application);
    const auto begin() const { return applications.begin(); }
    const auto end() const { return applications.end(); }
};

#endif //APPLICATIONS_HPP
