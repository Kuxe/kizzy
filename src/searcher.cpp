#include "searcher.hpp"
#include "fuzzysearch.hpp"

const SearchResults& Searcher::search(const char key) {
    searchString.add(key);
    FuzzySearch::search(searchString, directories, searchResults);
    return searchResults;
}

const SearchResults& Searcher::removeLastCharacter() {
    searchString.remove();
    FuzzySearch::search(searchString, directories, searchResults);
    return searchResults;
}

const std::string& Searcher::str() const {
    return searchString.get();
}

void Searcher::load(const Directory& directory) {
    directories.load(directory);
}
