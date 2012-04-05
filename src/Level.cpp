#include "Level.hpp"
#include "MapFileReader.hpp"
#include "Enemy.hpp"

Level::Level()
{

}

void Level::init()
{
	MapFileReader reader(this->getFilename());
	gameMap = reader.getMap();
}

Map Level::getMap()
{
	return gameMap;
}

