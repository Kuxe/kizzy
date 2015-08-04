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
	static constexpr ushort baseXOffset = 10;
	static constexpr ushort baseYOffset = 50;
	static constexpr ushort diffYOffset = 12;

	XColor backgroundColor;
	XColor foregroundColor;
	XColor selectedColor;

	Display* display = nullptr;
	int rootWindow;
	int screen;
	Colormap colormap;
	Window window;
	GC gc;

	void redraw() const;
	void highlightItemNumber(int itemNumber) const;
	void darkenItemNumber(int itemNumber) const;

public:
	X11View(int& status);
	~X11View();
};

#endif //x11view_hpp