#include "processlauncher.hpp"
#include "statusdefs.hpp"
#include <unistd.h>
#include <cstring>

//Takes an array of chars and splits it into an array of strings using space as delimiter
void split(char strargv[], char** argv) {
	int i = 0;
	char *token = strtok(strargv, " ");
    while(token != NULL) {
        argv[i++] = token;
        token = strtok(NULL, " ");
    }
}

int ProcessLauncher::launch(const std::string& execPath) {
	if(execPath.length() == 0) {
		return STATUS_CODE::OK;
	}

	//If the execPath points to an executable within a directory (such as /home/username/myprogram)
	//then set workingdirectory as (/home/username/)
	//if the execPath points to an executable in path (ie execPath = myprogram)
	//then do nothing
	const size_t workingDirectoryPos = execPath.find_last_of("/");
	if(workingDirectoryPos != std::string::npos) {
		const std::string workingDirectory = execPath.substr(0, workingDirectoryPos);
		if(chdir(workingDirectory.c_str()) == -1) {
			return STATUS_CODE::EXEC_FAILED;
		}
	}

	//If there is a space in execPath, ie there are args, split
	const size_t argsPos = execPath.find_first_of(" ");
	if(argsPos != std::string::npos) {

		//Copy the const char* of execPath.c_str() to non-const strargv
		char strargv[execPath.length()];
		strcpy(strargv, execPath.c_str());
		char* buffer[255];

		//For each word in strargv (ie execpath), let buffer[i] hold a pointer to beginning of that word
		//execvp wants a char** where each char[i] holds an argument
		int i = 0;
		char *token = strtok(strargv, " ");
	    while(token != NULL) {
	    	//Doesn't adhere to freedesktop desktop entry specification
	    	//See: http://standards.freedesktop.org/desktop-entry-spec/desktop-entry-spec-latest.html
	    	//This strips the %f code from any desktop file
	    	if(strcmp(token, "%F")) {
	    		buffer[i++] = token;
	    	}
	        token = strtok(NULL, " ");
	    }

	    //The variable i will be >= 1 due to the program name, so if i >= 2 then there have been args
	    if(i >= 2) {
			buffer[i+1] = NULL;
			if(execvp(buffer[0], buffer) < 0 ) {
				printf("Couldn't launch executable on %s (with args)\n", execPath.c_str());
				return STATUS_CODE::EXEC_FAILED;
			}
		} else {
			if(execlp(buffer[0], nullptr) == -1) {
				printf("Couldn't launch executable on %s (with args that was ignored)\n", execPath.c_str());
				return STATUS_CODE::EXEC_FAILED;
			}
		}
	} else {
		if(execlp(execPath.c_str(), nullptr) == -1) {
			printf("Couldn't launch executable on %s (wout args)\n", execPath.c_str());
			return STATUS_CODE::EXEC_FAILED;
		}
	}
	return STATUS_CODE::OK;
}