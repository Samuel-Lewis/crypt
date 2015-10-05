#include <cmath>
#include <vector>
#include <ncurses.h>

#include "lbLog.h"

#include "Engine.h"

Engine::Engine()
{
}

Engine::~Engine()
{
}

// Eventss
void Engine::addEvent(void (*function)())
{
	_events.push_back(function);
}

void Engine::removeEvent(void (*function)())
{
	// Want to iterate through all positions, to remove any duplicates
	for (unsigned i = 0; i < _events.size(); i++)
	{
		// If matches, remove it
		if (_events[i] == function)
		{
			_events.erase(_events.begin() + i);
		}
	}
}


// The mighty important tick
void Engine::tick()
{
	INFO(" >> TICK");
	
	// Call events
	for (unsigned i = 0; i < _events.size(); i++)
	{
		_events[i]();
	}
}
