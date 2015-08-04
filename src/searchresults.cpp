#include "searchresults.hpp"

const ApplicationMatching& SearchResults::operator[](int index) const {
	return results[index];
}

void SearchResults::insert(const ApplicationMatching& applicationMatching) {
    results.push_back(applicationMatching);
}

void SearchResults::clear() {
    results.clear();
}

bool SearchResults::empty() const {
	return results.empty();
}

size_t SearchResults::size() const {
	return results.size();
}
