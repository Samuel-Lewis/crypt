#ifndef CORE_UI_H
#define CORE_UI_H

#include <string>
#include <map>
#include <ncurses.h>

class UI
{
public:
	UI();
	~UI();

	void update();

	void setWin(std::string, std::string);
	void newWin(std::string, float, float, float, float);
	void newWin(std::string, int, int, int, int);

private:

	std::map<std::string, WINDOW*> _wins;

};

#endif // CORE_UI_H
