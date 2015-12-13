#ifndef PROCESSLAUNCHER_HPP
#define PROCESSLAUNCHER_HPP

#include <string>

/************************************************************
	Launches processes given the absolute-path execpath,
	using a working directory equal to that of the directory
	where the executable is located in
*************************************************************/
class ProcessLauncher {
public:
	static int launch(const std::string& execPath);
};

#endif //PROCESSLAUNCHER_HPP