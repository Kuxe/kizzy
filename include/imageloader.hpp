#ifndef IMAGELOADER_HPP
#define IMAGELOADER_HPP

#include <unordered_map>
#include <string>
#include <X11/Ximage.h>

/** Loads images, sherlock **/
class ImageLoader {
private:
	std::unordered_map<std::string, XImage*> images;
public:
	bool load(const std::string& imagePath);
	void unload(const std::string& imagePath);
	void unloadAll();
};

#endif //IMAGELOADER_HPP