#include "configloader.hpp"
#include <fstream>

bool ConfigLoader::loadConfig() {
	const std::string home = getenv("HOME");
	std::ifstream config(home + "/.config/kizzy/kizzy.conf");

	if(!config.is_open()) {
		return false;
	}


	std::string line;
	while(config.is_open() && getline(config, line)) {

		//Replace tilde by home
		if(line.front() == '~') {
			line.replace(0, 1, home);
		}
		directoryPaths.push_back(line);
	}

	config.close();
	return true;
}
void ConfigLoader::giveConfig(Searcher& searcher) const {
	for(const auto& directoryPath : directoryPaths) {
		searcher.load(directoryPath);
	}
}