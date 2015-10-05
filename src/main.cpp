#include <string>

#include <ncurses.h>

#include "lbLog.h"

#include "Core/Engine.h"
#include "Core/UI.h"

#include "Cartographer/Cartographer.h"
#include "Cartographer/Tile.h"

void foo()
{
	ERROR("FOO");
}

int main(int numArgs, char const *args[])
{
	// Check run flags
	for (int i = 0; i < numArgs; i++) {
		// Enable more verbose debug logs
		if (std::string(args[i]) == "-debug" || std::string(args[i]) == "-d") {
			lbLog::quickSet(lbLog::warn, lbLog::all, lbLog::fatal);
		}
	}

	lbLog::startLog("logs/", "crypt-log", true);
	Tile::loadTileLibrary("src/tileLib.csv");

	Cartographer test;
	Engine game;
	UI ui;

	ui.newWin("main",30,30,0,0);

	ui.setWin("main",test.getCurrentPrint());

	// void (UI::*pUpdate)() = &UI::update;
	// game.addEvent((ui.*pUpdate)());

	game.tick();

	lbLog::endLog();
	return 0;
}
