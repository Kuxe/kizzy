#include "processlauncher.hpp"
#include "statusdefs.hpp"
#include <unistd.h>

int ProcessLauncher::launch(const std::string& execPath) {
	if(execPath.length() == 0) {
		return STATUS_CODE::OK;
	}

	//If there is a space in execPath, ie there are args, split
	const size_t argsPos = execPath.find_first_of(" ");
	if(argsPos != std::string::npos) {
		if(execlp(execPath.substr(0, argsPos).c_str(), execPath.c_str()) == -1) {
			return STATUS_CODE::EXEC_FAILED;
		}
	} else {
		if(execlp(execPath.c_str(), nullptr) == -1) {
			return STATUS_CODE::EXEC_FAILED;
		}
	}
	return STATUS_CODE::OK;
}