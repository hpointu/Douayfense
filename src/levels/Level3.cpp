#include "Level3.hpp"

Level3::Level3() :
	Level()
{
}

std::string Level3::getFilename()
{
	return "map/level3.map";
}

int Level3::getBank()
{
	return 800;
}

int Level3::getHomePv()
{
	return 5;
}

std::vector<Wave> Level3::getWaves()
{
	std::vector<Wave> waves;

	std::vector<Enemy*> tmpStock;
	int i;

	// wave 1
	for(i=0; i<10; i++)
		tmpStock.push_back(new Enemy(gameMap.getDoors()[0], gameMap));
	waves.push_back(Wave(&gameMap, 1.0f));
	waves.back().initStock(tmpStock);
	waves.back().value = 150;
	tmpStock.clear();

	// wave 2
	for(i=0; i<10; i++)
		tmpStock.push_back(new Enemy(gameMap.getDoors()[0], gameMap));
	waves.push_back(Wave(&gameMap, 1/3.f));
	waves.back().initStock(tmpStock);
	waves.back().value = 180;
	waves.back().message = "";
	tmpStock.clear();

	// wave 3
	for(i=0; i<15; i++)
		tmpStock.push_back(new Enemy(gameMap.getDoors()[0], gameMap));
	waves.push_back(Wave(&gameMap, 1/4.f));
	waves.back().initStock(tmpStock);
	waves.back().message = "Courage :)";
	waves.back().value = 150;
	tmpStock.clear();

	// wave 4
	for(i=0; i<8; i++)
		tmpStock.push_back(new Enemy(gameMap.getDoors()[1], gameMap));
	waves.push_back(Wave(&gameMap, 1/2.f));
	waves.back().initStock(tmpStock);
	waves.back().message = "Attention !";
	waves.back().value = 100;
	tmpStock.clear();

	// wave 5
	for(i=0; i<16; i++)
		tmpStock.push_back(new Enemy(gameMap.getDoors()[i%2], gameMap));
	waves.push_back(Wave(&gameMap, 1/3.f));
	waves.back().initStock(tmpStock);
	waves.back().value = 60;
	tmpStock.clear();

	// wave 6
	for(i=0; i<20; i++)
		tmpStock.push_back(new Enemy(gameMap.getDoors()[i%2], gameMap));
	waves.push_back(Wave(&gameMap, 1/4.f));
	waves.back().initStock(tmpStock);
	waves.back().value = 70;
	tmpStock.clear();

	// wave 7
	for(i=0; i<28; i++)
		tmpStock.push_back(new Enemy(gameMap.getDoors()[i%2], gameMap));
	waves.push_back(Wave(&gameMap, 1/5.f));
	waves.back().value = 70;
	waves.back().initStock(tmpStock);
	tmpStock.clear();

	// wave 8
	for(i=0; i<35; i++)
		tmpStock.push_back(new Enemy(gameMap.getDoors()[i%2], gameMap));
	waves.push_back(Wave(&gameMap, 1/8.f));
	waves.back().initStock(tmpStock);
	waves.back().value = 50;
	tmpStock.clear();

	// wave 9
	for(i=0; i<45; i++)
		tmpStock.push_back(new Enemy(gameMap.getDoors()[i%2], gameMap));
	waves.push_back(Wave(&gameMap, 1/10.f));
	waves.back().initStock(tmpStock);
	waves.back().message = "Allez c'est la derniere !";
	waves.back().value = 500;
	tmpStock.clear();

	return waves;
}
