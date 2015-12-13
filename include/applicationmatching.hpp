#ifndef APPLICATIONMATCHING_HPP
#define APPLICATIONMATCHING_HPP

class Application;
class ApplicationMatching {
private:
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
