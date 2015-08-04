#include "x11view.hpp"
#include <X11/Xutil.h>
#include "statusdefs.hpp"
#include "processlauncher.hpp"
#include "configloader.hpp"

/** Private methods **/
void X11View::redraw() const {
	const std::string& str = searcher.str();

	XClearArea(display, window, 0, 12, 0, 8, false);
	XSetForeground(display, gc, selectedColor.pixel);
	XDrawString(display, window, gc, baseXOffset, 20, str.c_str(), str.length());

	int itemNum = 0;
	for(const ApplicationMatching& applicationMatching : *searchResults) {
		itemNum == selectedItem ? highlightItemNumber(itemNum) : darkenItemNumber(itemNum);
		itemNum += 1;
	}
	XClearArea(display, window, 0, baseYOffset + diffYOffset * (itemNum-1), 0, 0, false);
}

void X11View::highlightItemNumber(int itemNumber) const {
	//Clear area of itemNumber
	XClearArea(display, window, 0, 2 + baseYOffset + diffYOffset * (itemNumber-1), 0, 10, false);

	//Repaint itemNumber area with highlightning
	const std::string& selectedAppname = ">" + (*searchResults)[itemNumber].getApplication()->getName() + "<";
	XSetForeground(display, gc, selectedColor.pixel);
	XDrawString(display, window, gc, 4, baseYOffset + diffYOffset * itemNumber, selectedAppname.c_str(), selectedAppname.length());
	XSetForeground(display, gc, foregroundColor.pixel);
}

void X11View::darkenItemNumber(int itemNumber) const {
	//Clear area of old currentSelected item
	XClearArea(display, window, 0, 2 + baseYOffset + diffYOffset * (itemNumber-1), 0, 10, false);

	//Repaint itemNumber area without highlightning
	const std::string& appname = (*searchResults)[itemNumber].getApplication()->getName();
	XDrawString(display, window, gc, baseXOffset, baseYOffset + diffYOffset * itemNumber, appname.c_str(), appname.length());
}

/** Public methods **/
X11View::X11View(int& status) :
	//Doesn't actually need to removeLastCharacter, but pointer to searchresults can be set this way :)
	searchResults(&searcher.removeLastCharacter()) {
	status = STATUS_CODE::OK;

	//Load directories with .desktop files from kizzy.conf
	{
		ConfigLoader configLoader;
		if(configLoader.loadConfig()) {
			configLoader.giveConfig(searcher);
		} else {
			status = STATUS_CODE::CONFIGLOAD_FAILED;
			return;
		}
	}


	if(!(display = XOpenDisplay(nullptr))) {
		status = STATUS_CODE::XOPENDISPLAY_FAILED;
		return;
	}

	rootWindow = DefaultRootWindow(display);
	screen = DefaultScreen(display);
	colormap = DefaultColormap(display, screen);
	gc = DefaultGC(display, screen);

	//Load some colors
	constexpr char RGB_FLAGS = DoRed | DoGreen | DoBlue;
	backgroundColor.red = 0x2121; backgroundColor.green = 0x2121; backgroundColor.blue = 0x2121;
	backgroundColor.flags = RGB_FLAGS;
	XAllocColor(display, colormap, &backgroundColor);

	foregroundColor.red = 0xBBBB; foregroundColor.green = 0xBBBB; foregroundColor.blue = 0xBBBB;
	foregroundColor.flags = RGB_FLAGS;
	XAllocColor(display, colormap, &foregroundColor);

	selectedColor.red = 0xFFFF; selectedColor.green = 0xFFFF; selectedColor.blue = 0xFFFF;
	selectedColor.flags = RGB_FLAGS;
	XAllocColor(display, colormap, &selectedColor);

	window = XCreateSimpleWindow(display, rootWindow, 0, 0, 200, 100, 0, foregroundColor.pixel, backgroundColor.pixel);
	XSetForeground(display, gc, foregroundColor.pixel);

	if(!(font = XLoadFont(display, "-*-terminesspowerline-*-*-*-*-*-*-*-*-*-*-*-*"))) {
		status = STATUS_CODE::XLOADFONT_FAILED;
		return;
	}

	XSetFont(display, gc, font);

	//Only react to Exposure-event and KeyPress-event
	XSelectInput(display, window, KeyPressMask);
	XMapWindow(display, window);

	//I honestly don't know. Got it off internet. For proper, I think, closing of X11-window
	Atom WM_DELETE_WINDOW = XInternAtom(display, "WM_DELETE_WINDOW", False);
	XSetWMProtocols(display, window, &WM_DELETE_WINDOW, 1);

	XEvent event;

	char chr;
	KeySym keysym;

	while(true) {

		//Get event from X-server
		XNextEvent(display, &event);

		switch(event.type) {
			case KeyPress: {

				//Save the keypress to chr
				XLookupString(&event.xkey, &chr, sizeof chr, &keysym, nullptr);

				//On backspace, remove the last character from searcher and save
				//This is safe because searcher owns the searchresults internally
				switch(keysym) {

					case XK_Down: {

						//Only allow increasing selectedItem if not about exceed result size
						//Can't select an item outside searchResults...
						if(selectedItem + 1 < searchResults->size()) {
							darkenItemNumber(selectedItem);
							highlightItemNumber(selectedItem += 1);
						}
					} break;
					
					case XK_Up: {
						if(selectedItem > 0) {
							darkenItemNumber(selectedItem);
							highlightItemNumber(selectedItem -= 1);
						}
					} break;

					case XK_BackSpace: {
						selectedItem = 0;
						searchResults = &searcher.removeLastCharacter();
						redraw();
					} break;

					case XK_Return: {
						if(!searchResults->empty()) {
							const Application* bestMatch = (*searchResults)[selectedItem].getApplication();
							status = ProcessLauncher::launch((*searchResults)[selectedItem].getApplication()->getExec());
						}
						return;
					} break;

					case XK_Escape: {
						return;
					} break;

					//TODO: Only accept characters from alphabets here
					//Put the typed character into the searcher
					default: {
						selectedItem = 0;
						searchResults = &searcher.search(chr);
						redraw();
					} break;
				} //endof switch

			} break;

			//If a close window event was received, return out of the method
			case ClientMessage: {
				if(event.xclient.data.l[0] == WM_DELETE_WINDOW) {
					return;
				}
			} break;
		} //endof switch
	}
}

X11View::~X11View() {
	if(font) {
  		XUnloadFont(display, font);
  	}

	//Only cleanup if initialization worked out
	if(display != nullptr) {
		XDestroyWindow(display, window);
  		XCloseDisplay(display);
  	}
}