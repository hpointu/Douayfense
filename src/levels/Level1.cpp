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

	// wave 1
	for(i=0; i<10; i++)
		tmpStock.push_back(Enemy(gameMap.getDoors()[0], gameMap));
	waves.push_back(Wave(&gameMap, 1.6f));
	waves.back().initStock(tmpStock);
	tmpStock.clear();

	// wave 2
	for(i=0; i<10; i++)
		tmpStock.push_back(Enemy(gameMap.getDoors()[0], gameMap));
	waves.push_back(Wave(&gameMap, 1/1.f));
	waves.back().initStock(tmpStock);
	tmpStock.clear();

	// wave 3
	for(i=0; i<15; i++)
		tmpStock.push_back(Enemy(gameMap.getDoors()[0], gameMap));
	waves.push_back(Wave(&gameMap, 1/2.f));
	waves.back().initStock(tmpStock);
	waves.back().message = "Prochain coup, ca vient du bas !";
	tmpStock.clear();

	// wave 4
	for(i=0; i<8; i++)
		tmpStock.push_back(Enemy(gameMap.getDoors()[1], gameMap));
	waves.push_back(Wave(&gameMap, 1/1.f));
	waves.back().initStock(tmpStock);
	tmpStock.clear();

	// wave 5
	for(i=0; i<16; i++)
		tmpStock.push_back(Enemy(gameMap.getDoors()[i%2], gameMap));
	waves.push_back(Wave(&gameMap, 1/2.f));
	waves.back().initStock(tmpStock);
	tmpStock.clear();

	// wave 6
	for(i=0; i<20; i++)
		tmpStock.push_back(Enemy(gameMap.getDoors()[i%2], gameMap));
	waves.push_back(Wave(&gameMap, 1/4.f));
	waves.back().initStock(tmpStock);
	tmpStock.clear();

	// wave 7
	for(i=0; i<28; i++)
		tmpStock.push_back(Enemy(gameMap.getDoors()[i%2], gameMap));
	waves.push_back(Wave(&gameMap, 1/8.f));
	waves.back().initStock(tmpStock);
	tmpStock.clear();

	// wave 8
	for(i=0; i<35; i++)
		tmpStock.push_back(Enemy(gameMap.getDoors()[i%2], gameMap));
	waves.push_back(Wave(&gameMap, 1/9.f));
	waves.back().initStock(tmpStock);
	tmpStock.clear();

	// wave 9
	for(i=0; i<55; i++)
		tmpStock.push_back(Enemy(gameMap.getDoors()[i%2], gameMap));
	waves.push_back(Wave(&gameMap, 1/12.f));
	waves.back().initStock(tmpStock);
	waves.back().message = "Allez c'est la derniere !";
	tmpStock.clear();

	return waves;
}
