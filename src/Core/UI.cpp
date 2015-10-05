#include <cmath>
#include <vector>
#include <ncurses.h>

#include "lbLog.h"

#include "UI.h"

UI::UI()
{
	// Initiaize ncurses
	initscr();

	if (has_colors() == FALSE)
	{
		WARN("Your terminal does not support colours. Sorry :(");
	}

	raw();
	noecho();

	refresh();
}

UI::~UI()
{
	// End your ncurses kids
	endwin();
}

// The mighty important tick
void UI::update()
{
	INFO("UI Update");
	
	// Set screens
	for (auto const& entry : _wins)
	{
		wrefresh(entry.second);
	}

	// temp pausing
	getch();

}

// Set the contents of the window, ready for tick();
void UI::setWin(std::string winName, std::string content)
{
	wprintw(_wins[winName], content.c_str());
}

// Create new ncurses window
void UI::newWin(std::string winName, int height, int width, int startX, int startY)
{
	_wins[winName] = newwin(height,width,startX,startY);
	box(_wins[winName],0,0);
}


void UI::newWin(std::string winName, float heightProp, float widthProp, float startXProp, float startYProp)
{
	// Convert proportions into actual values
	int width = round(widthProp * COLS);
	int height = round(heightProp * LINES);
	int startX = round(startXProp * COLS);
	int startY = round(startYProp * LINES);

	newWin(winName,height,width,startX,startY);
}
