#ifndef x11view_HPP
#define x11view_HPP

#include <X11/Xlib.h>
#include "searcher.hpp"

class X11View {
private:
	Searcher searcher;
	const SearchResults* searchResults;

	//Represents the selectedItem in the list
	//0 would be the topmost item, the best match
	//pressing UP or DOWN (arrow) on keyboard will
	//increment and decrement this
	//Typing or erasing will reset it to zero.
	char selectedItem = 0;
	static constexpr ushort TOP_PADDING = 25;
	static constexpr ushort PADDING = 10;
	static constexpr ushort WINDOW_WIDTH = 225;
	static constexpr ushort WINDOW_HEIGHT = 500;
	static constexpr ushort DIFF_Y_OFFSET = 12;		//y-gap between items

	//These are queried later on
	ushort screenWidth;
	ushort screenHeight;

	XColor backgroundColor;		//Background color
	XColor foregroundColor; 	//Default text color
	XColor selectedColor; 		//Color of selected item
	XColor arrowColor;			//Color of arrows surrounding selected item
	XColor searchColor;			//Color of the searchstring

	Display* display = nullptr;
	int rootWindow;
	int screen;
	Colormap colormap;
	Window window;
	GC gc;

	void redraw() const;
	void highlightItemNumber(int itemNumber) const;
	void darkenItemNumber(int itemNumber) const;
	void paintPadding() const;

public:
	X11View(int& status);
	~X11View();
};

#endif //x11view_hpp