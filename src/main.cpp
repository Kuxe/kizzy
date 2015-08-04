#include "x11view.hpp"

//TODO: Image loading
//TODO: Image background
//TODO: Top item display bigger text and icon
//TODO: Anti-aliased font
//TODO: Floating on tiled
//TODO: Rounded corners if possible
//TODO: Fix that bug where kizzy remains open after, supposed, termination
//TODO: Setup github
//TODO: Add to AUR
//TODO: Cleanup code
//TODO: Optimize
//TODO: Abandon

/** Build instructions**/
//1: 			Go to project root
//2: 			create two folders: release + debug
//3.debug:    	cd debug && cmake -DCMAKE_BUILD_TYPE=Debug .. && make
//3.release:  	cd release && cmake -DCMAKE_BUILD_TYPE=Release .. && make
int main(int argc, char* argv[]) {
	int status;
	X11View view(status);
    return status;
}
