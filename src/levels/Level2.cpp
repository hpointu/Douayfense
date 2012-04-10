#include "Level2.hpp"

Level2::Level2() :
	Level()
{
}

std::string Level2::getFilename()
{
	return "map/level2.map";
}

int Level2::getBank()
{
	return 850;
}

int Level2::getHomePv()
{
	return 5;
}

std::vector<Wave> Level2::getWaves()
{
	std::vector<Wave> waves;

	std::vector<Enemy*> tmpStock;
	int i;

	// wave 1
	for(i=0; i<10; i++)
		tmpStock.push_back(new Enemy(gameMap.getDoors()[0], gameMap));
	waves.push_back(Wave(&gameMap, 1.6f));
	waves.back().initStock(tmpStock);
	waves.back().value = 150;
	tmpStock.clear();

	// wave 2
	for(i=0; i<12; i++)
		tmpStock.push_back(new Enemy(gameMap.getDoors()[1], gameMap));
	waves.push_back(Wave(&gameMap, 1.4f));
	waves.back().initStock(tmpStock);
	waves.back().value = 150;
	waves.back().message = "Dans ton cul :)";
	tmpStock.clear();

	// wave 3
	for(i=0; i<15; i++)
		tmpStock.push_back(new Enemy(gameMap.getDoors()[i%2], gameMap));
	waves.push_back(Wave(&gameMap, 1.0f));
	waves.back().initStock(tmpStock);
	waves.back().message = "";
	waves.back().value = 150;
	tmpStock.clear();

	// wave 4
	for(i=0; i<18; i++)
		tmpStock.push_back(new Enemy(gameMap.getDoors()[i%2], gameMap));
	waves.push_back(Wave(&gameMap, 1/3.f));
	waves.back().initStock(tmpStock);
	waves.back().value = 200;
	tmpStock.clear();

	// wave 5
	for(i=0; i<20; i++)
		tmpStock.push_back(new Enemy(gameMap.getDoors()[i%2], gameMap));
	waves.push_back(Wave(&gameMap, 1/5.f));
	waves.back().initStock(tmpStock);
	waves.back().value = 150;
	tmpStock.clear();

	// wave 6
	for(i=0; i<22; i++)
		tmpStock.push_back(new Enemy(gameMap.getDoors()[i%2], gameMap));
	waves.push_back(Wave(&gameMap, 1/6.f));
	waves.back().initStock(tmpStock);
	waves.back().value = 200;
	tmpStock.clear();

	// wave 7
	for(i=0; i<25; i++)
		tmpStock.push_back(new Enemy(gameMap.getDoors()[i%2], gameMap));
	waves.push_back(Wave(&gameMap, 1/8.f));
	waves.back().value = 250;
	waves.back().message = "Tiens bon !";
	waves.back().initStock(tmpStock);
	tmpStock.clear();

	// wave 8
	for(i=0; i<25; i++)
		tmpStock.push_back(new Enemy(gameMap.getDoors()[i%2], gameMap));
	waves.push_back(Wave(&gameMap, 1/10.f));
	waves.back().initStock(tmpStock);
	waves.back().value = 250;
	tmpStock.clear();

	// wave 9
	for(i=0; i<30; i++)
		tmpStock.push_back(new Enemy(gameMap.getDoors()[i%2], gameMap));
	waves.push_back(Wave(&gameMap, 1/10.f));
	waves.back().initStock(tmpStock);
	waves.back().message = "Allez c'est la derniere !";
	waves.back().value = 500;
	tmpStock.clear();

	return waves;
}
