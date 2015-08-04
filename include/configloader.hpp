#ifndef CONFIGLOADER_HPP
#define CONFIGLOADER_HPP

#include <vector>
#include <string>
#include "searcher.hpp"


/** Reads the kizzy.conf file and makes a searcher use those settings **/
/** Assumes ~/.config/kizzy/kizzy.conf as location of configuration file **/
class ConfigLoader {
private:
	std::vector<std::string> directoryPaths;
public:
	bool loadConfig();
	void giveConfig(Searcher& searcher) const;
};


#endif //CONFIGLOADER_HPP