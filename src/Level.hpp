#ifndef LEVEL_HPP
#define LEVEL_HPP

#include "Map.hpp"
#include "Wave.hpp"

#include <string>
#include <vector>

class Level
{
public:
	Level();
	void init();
	Map getMap();

	virtual std::string getFilename() = 0;
	virtual std::vector<Wave> getWaves() = 0;
	virtual int getBank() = 0;
	virtual int getHomePv() = 0;

protected:
	Map gameMap;
};

#endif // LEVEL_HPP
