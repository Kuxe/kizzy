#include "x11view.hpp"
#include <X11/Xutil.h>
#include "statusdefs.hpp"
#include "processlauncher.hpp"
#include "configloader.hpp"

/** Private methods **/
void X11View::redraw() {

	//Only trigger resize if windowHeight actually changed
	const auto newWindowHeight = TOP_PADDING + DIFF_Y_OFFSET * searchResults->size();
	if(newWindowHeight != windowHeight) {
		windowHeight = newWindowHeight;
		XResizeWindow(display, window, WINDOW_WIDTH, windowHeight);
	}

	const std::string& str = searcher.str();

	XClearArea(display, window, 0, 0, 0, 14, false);
	XSetForeground(display, gc, searchColor.pixel);
	XDrawString(display, window, gc, PADDING, 12, str.c_str(), str.length());

	int itemNum = 0;
	for(const ApplicationMatching& applicationMatching : *searchResults) {
		itemNum == selectedItem ? highlightItemNumber(itemNum) : darkenItemNumber(itemNum);
		itemNum += 1;
	}

	//Clear away old results
	XClearArea(display, window, 0, TOP_PADDING + DIFF_Y_OFFSET * (itemNum-1), 0, 0, false);

	paintPadding();
}

void X11View::highlightItemNumber(int itemNumber) const {
	XClearArea(display, window, 0, 2 + TOP_PADDING + DIFF_Y_OFFSET * (itemNumber-1), 0, 12, false);

	//Repaint itemNumber area with highlightning
	//Hacky code here... drawing string _with_ arrows using arrow color
	//then drawing string without arrows using stringcolor ontop of that..
	//painters algorithm!
	const std::string& selectedAppnameArrows = ">" + (*searchResults)[itemNumber].getApplication()->getName() + "<";
	XSetForeground(display, gc, arrowColor.pixel);
	XDrawString(display, window, gc, 4, TOP_PADDING + DIFF_Y_OFFSET * itemNumber, selectedAppnameArrows.c_str(), selectedAppnameArrows.length());

	//Draw only string
	const std::string& selectedAppname = (*searchResults)[itemNumber].getApplication()->getName();
	XSetForeground(display, gc, selectedColor.pixel);
	XDrawString(display, window, gc, 10, TOP_PADDING + DIFF_Y_OFFSET * itemNumber, selectedAppname.c_str(), selectedAppname.length());

	XSetForeground(display, gc, foregroundColor.pixel);
}

void X11View::darkenItemNumber(int itemNumber) const {
	//Clear area of itemNumber
	XClearArea(display, window, 0, 2 + TOP_PADDING + DIFF_Y_OFFSET * (itemNumber-1), 0, 12, false);

	//Repaint itemNumber area without highlightning
	const std::string& appname = (*searchResults)[itemNumber].getApplication()->getName();
	XDrawString(display, window, gc, PADDING, TOP_PADDING + DIFF_Y_OFFSET * itemNumber, appname.c_str(), appname.length());
}

void X11View::paintPadding() const {
	//Clear right-side of screen (make some padding between items and border)
	XClearArea(display, window, WINDOW_WIDTH - PADDING, 0, 0, 0, false);

	//Clear bottom-side of screen (make some padding between items and border)
	XClearArea(display, window, 0, windowHeight - PADDING, 0, 0, false);
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

	//Query screenWidth and screenHeight
	screenWidth = WidthOfScreen(DefaultScreenOfDisplay(display));
	screenHeight = HeightOfScreen(DefaultScreenOfDisplay(display));


	//Load some colors
	constexpr char RGB_FLAGS = DoRed | DoGreen | DoBlue;
	backgroundColor.red = 0x2121; backgroundColor.green = 0x2121; backgroundColor.blue = 0x2121;
	backgroundColor.flags = RGB_FLAGS;
	XAllocColor(display, colormap, &backgroundColor);

	foregroundColor.red = 0x3B3B; foregroundColor.green = 0x5353; foregroundColor.blue = 0x8484;
	foregroundColor.flags = RGB_FLAGS;
	XAllocColor(display, colormap, &foregroundColor);

	selectedColor.red = 0xCCCC; selectedColor.green = 0x6C6C; selectedColor.blue = 0xA5A5;
	selectedColor.flags = RGB_FLAGS;
	XAllocColor(display, colormap, &selectedColor);


	arrowColor.red = 0x7777; arrowColor.green = 0x8989; arrowColor.blue = 0xB8B8;
	arrowColor.flags = RGB_FLAGS;
	XAllocColor(display, colormap, &arrowColor);

	searchColor.red = 0xFFFF; searchColor.green = 0xFFFF; searchColor.blue = 0xFFFF;
	searchColor.flags = RGB_FLAGS;
	XAllocColor(display, colormap, &searchColor);

	//Create window in center of screen
	XSetWindowAttributes xswa;
	xswa.background_pixel = backgroundColor.pixel;
	const long mask = CWBackPixel;
	const short x = (screenWidth/2) - (WINDOW_WIDTH/2), y = (screenHeight/2) - (windowHeight/2);

	window = XCreateWindow(
		display,
		rootWindow,
		x, y,
		WINDOW_WIDTH, windowHeight,
		0,
		CopyFromParent,
		InputOutput,
		CopyFromParent,
		mask,
		&xswa
	);

	XSetForeground(display, gc, foregroundColor.pixel);

	//Set window class name to "kizzy"
	char programName[] {"kizzy"};
	auto classHint = XAllocClassHint();
	classHint->res_name = programName;
	classHint->res_class = programName;
	XSetClassHint(display, window, classHint);



	//Only react to Exposure-event and KeyPress-event
	XSelectInput(display, window, KeyPressMask | StructureNotifyMask);
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

			//Redraw on resize
			case ConfigureNotify: {
				redraw();
			} break;

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
							paintPadding();
						}
					} break;
					
					case XK_Up: {
						if(selectedItem > 0) {
							darkenItemNumber(selectedItem);
							highlightItemNumber(selectedItem -= 1);
							paintPadding();
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
	//Only cleanup if initialization worked out
	if(display != nullptr) {
		XDestroyWindow(display, window);
  		XCloseDisplay(display);
  	}
}