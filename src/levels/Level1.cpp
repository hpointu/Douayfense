#include "Level1.hpp"

Level1::Level1() :
	Level()
{
}

std::string Level1::getFilename()
{
	return "map/level1.map";
}

int Level1::getBank()
{
	return 800;
}

int Level1::getHomePv()
{
	return 5;
}

std::vector<Wave> Level1::getWaves()
{
	std::vector<Wave> waves;

	std::vector<Enemy> tmpStock;
	int i;

	// first wave
	for(i=0; i<15; i++)
		tmpStock.push_back(Enemy(gameMap.getDoors()[0], gameMap));
	waves.push_back(Wave(&gameMap, 1.3f));
	waves.back().initStock(tmpStock);
	tmpStock.clear();

	// second wave
	for(i=0; i<15; i++)
		tmpStock.push_back(Enemy(gameMap.getDoors()[0], gameMap));
	waves.push_back(Wave(&gameMap, 1/1.f));
	waves.back().initStock(tmpStock);
	tmpStock.clear();

	// third wave
	for(i=0; i<18; i++)
		tmpStock.push_back(Enemy(gameMap.getDoors()[0], gameMap));
	waves.push_back(Wave(&gameMap, 1/2.f));
	waves.back().initStock(tmpStock);
	tmpStock.clear();

	// fourth wave
	for(i=0; i<16; i++)
		tmpStock.push_back(Enemy(gameMap.getDoors()[i%2], gameMap));
	waves.push_back(Wave(&gameMap, 1/4.f));
	waves.back().initStock(tmpStock);
	tmpStock.clear();

	// fifth wave
	for(i=0; i<20; i++)
		tmpStock.push_back(Enemy(gameMap.getDoors()[i%2], gameMap));
	waves.push_back(Wave(&gameMap, 1/5.f));
	waves.back().initStock(tmpStock);
	tmpStock.clear();

	// sixth wave
	for(i=0; i<28; i++)
		tmpStock.push_back(Enemy(gameMap.getDoors()[i%2], gameMap));
	waves.push_back(Wave(&gameMap, 1/8.f));
	waves.back().initStock(tmpStock);
	tmpStock.clear();

	// seventh wave
	for(i=0; i<45; i++)
		tmpStock.push_back(Enemy(gameMap.getDoors()[i%2], gameMap));
	waves.push_back(Wave(&gameMap, 1/10.f));
	waves.back().initStock(tmpStock);
	tmpStock.clear();

	return waves;
}
