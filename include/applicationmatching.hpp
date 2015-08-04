#ifndef APPLICATIONMATCHING_HPP
#define APPLICATIONMATCHING_HPP

#include <ostream>

class Application;
class ApplicationMatching {
private:
    friend std::ostream& operator<< (std::ostream& stream, const ApplicationMatching& applicationMatching);

    float rank;
    const Application* application;

public:
    ApplicationMatching(float rank, const Application* application);

    bool operator<(const ApplicationMatching& rhs) const { return rank < rhs.rank; }
    bool operator>(const ApplicationMatching& rhs) const { return rank > rhs.rank; }
    bool operator<=(const ApplicationMatching& rhs) const { return !(*this > rhs); }
    bool operator>=(const ApplicationMatching& rhs) const { return !(*this < rhs); }
    bool operator==(const ApplicationMatching& rhs) const { return rank == rhs.rank; }

    float getRank() const;
    const Application* getApplication() const;
};

#endif //APPLICATIONMATCHING_HPP
