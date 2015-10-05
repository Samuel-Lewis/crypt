#ifndef CORE_ENGINE_H
#define CORE_ENGINE_H

#include <string>
#include <vector>
#include <map>

class Engine
{
public:
	Engine();
	~Engine();

	void addEvent(void (*)());
	void removeEvent(void (*)());

	void tick();

private:
	std::vector<void (*)()> _events;

};

#endif // CORE_ENGINE_H
