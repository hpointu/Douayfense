#include "Level3.hpp"
#include "../Gobelin.hpp"
#include "../Drake.hpp"

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
	return 1000;
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
	waves.back().value = 400;
	tmpStock.clear();

	// wave 2
	for(i=0; i<10; i++)
		tmpStock.push_back(new Gobelin(gameMap.getDoors()[0], gameMap));
	waves.push_back(Wave(&gameMap, 1/3.f));
	waves.back().initStock(tmpStock);
	waves.back().value = 550;
	waves.back().message = "";
	tmpStock.clear();

	// wave 3
	tmpStock.push_back(new Gobelin(gameMap.getDoors()[1], gameMap));
	for(i=0; i<8; i++)
	{
		tmpStock.push_back(new Enemy(gameMap.getDoors()[0], gameMap));
		tmpStock.push_back(new Gobelin(gameMap.getDoors()[0], gameMap));
		tmpStock.push_back(new Gobelin(gameMap.getDoors()[0], gameMap));
		tmpStock.back()->waveWait = 1/5.f;
		tmpStock.push_back(new Gobelin(gameMap.getDoors()[0], gameMap));
		tmpStock.back()->waveWait = 1/5.f;
	}
	tmpStock.push_back(new Gobelin(gameMap.getDoors()[2], gameMap));
	waves.push_back(Wave(&gameMap, 1/2.f));
	waves.back().initStock(tmpStock);
	waves.back().message = "Courage :)";
	waves.back().value = 650;
	tmpStock.clear();

	// wave 4
	for(i=0; i<4; i++)
	{
		tmpStock.push_back(new Enemy(gameMap.getDoors()[1], gameMap));
		tmpStock.push_back(new Drake(gameMap.getDoors()[2], gameMap));
		tmpStock.push_back(new Gobelin(gameMap.getDoors()[0], gameMap));
		tmpStock.back()->waveWait = 1/6.f;
		tmpStock.push_back(new Gobelin(gameMap.getDoors()[0], gameMap));
		tmpStock.back()->waveWait = 1/6.f;
		tmpStock.push_back(new Enemy(gameMap.getDoors()[1], gameMap));
		tmpStock.push_back(new Gobelin(gameMap.getDoors()[0], gameMap));
		tmpStock.back()->waveWait = 1/6.f;
		tmpStock.push_back(new Gobelin(gameMap.getDoors()[0], gameMap));
		tmpStock.back()->waveWait = 1/6.f;
	}
	waves.push_back(Wave(&gameMap, 1/3.f));
	waves.back().initStock(tmpStock);
	waves.back().message = "Attention !";
	waves.back().value = 850;
	tmpStock.clear();

	// wave 5
	for(i=0; i<22; i++)
	{
		tmpStock.push_back(new Enemy(gameMap.getDoors()[i%3], gameMap));
		tmpStock.push_back(new Gobelin(gameMap.getDoors()[i%3], gameMap));
		tmpStock.push_back(new Gobelin(gameMap.getDoors()[i%3], gameMap));
		tmpStock.back()->waveWait = 1/6.f;
		tmpStock.push_back(new Gobelin(gameMap.getDoors()[i%3], gameMap));
		tmpStock.back()->waveWait = 1/6.f;
	}
	waves.push_back(Wave(&gameMap, 1/5.f));
	waves.back().initStock(tmpStock);
	waves.back().value = 800;
	tmpStock.clear();

	return waves;
}
