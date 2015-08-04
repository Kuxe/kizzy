#ifndef SEARCHER_HPP
#define SEARCHER_HPP

#include "searchresults.hpp"
#include "searchstring.hpp"
#include "directories.hpp"

/** Can add, remove and clear characters
    Searching is implicit on adding, removing and clearing
    Use results() to get results from searching

    Search will be performed within the directories that
    have been loaded using load(). Directories can be unloaded
    at runtime using unload().
**/
class Searcher {
private:
    SearchString searchString;
    SearchResults searchResults;
    Directories directories;

public:
    const SearchResults& search(const char keypress);
    const SearchResults& removeLastCharacter();
    const std::string& str() const;
    void load(const Directory& directory);
};


#endif //SEARCHER_HPP
