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
	for(i=0; i<1; i++)
		tmpStock.push_back(Enemy(gameMap.getDoors()[0], gameMap));
	waves.push_back(Wave(&gameMap, 1.8f));
	waves.back().initStock(tmpStock);
	waves.back().value = 250;
	tmpStock.clear();

	// wave 2
	for(i=0; i<1; i++)
		tmpStock.push_back(Enemy(gameMap.getDoors()[0], gameMap));
	waves.push_back(Wave(&gameMap, 1.5f));
	waves.back().initStock(tmpStock);
	waves.back().value = 200;
	waves.back().message = "Les ennemis pourraient arriver du bas...";
	tmpStock.clear();

//	// wave 3
//	for(i=0; i<15; i++)
//		tmpStock.push_back(Enemy(gameMap.getDoors()[0], gameMap));
//	waves.push_back(Wave(&gameMap, 1/1.f));
//	waves.back().initStock(tmpStock);
//	waves.back().message = "Protegez le sud le plus vite possible !";
//	waves.back().value = 200;
//	tmpStock.clear();

//	// wave 4
//	for(i=0; i<8; i++)
//		tmpStock.push_back(Enemy(gameMap.getDoors()[1], gameMap));
//	waves.push_back(Wave(&gameMap, 1/1.f));
//	waves.back().initStock(tmpStock);
//	waves.back().value = 180;
//	tmpStock.clear();

//	// wave 5
//	for(i=0; i<16; i++)
//		tmpStock.push_back(Enemy(gameMap.getDoors()[i%2], gameMap));
//	waves.push_back(Wave(&gameMap, 1/2.f));
//	waves.back().initStock(tmpStock);
//	waves.back().value = 200;
//	waves.back().message = "C'est la derniere vague !";
//	tmpStock.clear();


	return waves;
}
