#ifndef PROCESSLAUNCHER_HPP
#define PROCESSLAUNCHER_HPP

#include <string>

class ProcessLauncher {
public:
	static int launch(const std::string& execPath);
};

#endif //PROCESSLAUNCHER_HPP