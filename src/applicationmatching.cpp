#include "applicationmatching.hpp"
#include "application.hpp"

std::ostream& operator<<(std::ostream& stream, const ApplicationMatching& am) {
    stream << "{" << am.getApplication()->getName() << ", " << am.getRank() << "}";
}

ApplicationMatching::ApplicationMatching(float rank, const Application* application) :
    rank(rank), application(application) {

}

float ApplicationMatching::getRank() const {
    return rank;
}

const Application* ApplicationMatching::getApplication() const {
    return application;
}
