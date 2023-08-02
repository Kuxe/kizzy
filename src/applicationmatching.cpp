#include "../include/applicationmatching.hpp"
#include "../include/application.hpp"

ApplicationMatching::ApplicationMatching(float rank, const Application* application) :
    rank(rank), application(application) {

}

float ApplicationMatching::getRank() const {
    return rank;
}

const Application* ApplicationMatching::getApplication() const {
    return application;
}
