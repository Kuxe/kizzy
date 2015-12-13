#ifndef SEARCHRESULTS_HPP
#define SEARCHRESULTS_HPP

#include <vector>
#include <cstddef>
#include "applicationmatching.hpp"

/** Represents results from a search
    This is the one you want to pass onto a view-class
**/
class SearchResults {
private:
    std::vector<ApplicationMatching> results;

public:
	const ApplicationMatching& operator[](int index) const;

    void insert(const ApplicationMatching& applicationMatching);
    void clear();
    bool empty() const;
    size_t size() const;

    const auto begin() const { return results.begin(); }
    const auto end() const { return results.end(); }
};

#endif //SEARCHRESULTS_HPP
