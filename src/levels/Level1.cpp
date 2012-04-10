#include "Level1.hpp"
#include "../Gobelin.hpp"
#include "../Drake.hpp"

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
	return 1000;
}

int Level1::getHomePv()
{
	return 5;
}

std::vector<Wave> Level1::getWaves()
{
	std::vector<Wave> waves;

	std::vector<Enemy*> tmpStock;
	int i;

	// wave 1
	for(i=0; i<6; i++)
	{
		tmpStock.push_back(new Enemy(gameMap.getDoors()[0], gameMap));
	}
	waves.push_back(Wave(&gameMap, 1.8f));
	waves.back().initStock(tmpStock);
	waves.back().value = 300;
	waves.back().message = "La touche ESPACE permet de mettre en pause.\n"
			"Les touches A,Z,E permettent d'acheter des tours.";
	tmpStock.clear();

	// wave 2
	for(i=0; i<10; i++)
	{
		tmpStock.push_back(new Gobelin(gameMap.getDoors()[0], gameMap));
	}
	waves.push_back(Wave(&gameMap, 1/3.f));
	waves.back().initStock(tmpStock);
	waves.back().value = 300;
	waves.back().message = "Les gobelins sont rapides, mais peu resistants aux attaques.";
	tmpStock.clear();

	// wave 3
	for(i=0; i<5; i++)
	{
		tmpStock.push_back(new Enemy(gameMap.getDoors()[0], gameMap));
	}
	for(i=0; i<5; i++)
	{
		tmpStock.push_back(new Gobelin(gameMap.getDoors()[0], gameMap));
		tmpStock.back()->waveWait = 1/3.f;
	}
	waves.push_back(Wave(&gameMap, 1/1.f));
	waves.back().initStock(tmpStock);
	waves.back().value = 300;
	waves.back().message = "";
	tmpStock.clear();

	// wave 4
	for(i=0; i<4; i++)
	{
		tmpStock.push_back(new Drake(gameMap.getDoors()[0], gameMap));
	}
	waves.push_back(Wave(&gameMap, 1.6f));
	waves.back().initStock(tmpStock);
	waves.back().value = 300;
	waves.back().message = "Les dragons resistent au froid, qui ne peut les ralentir.\n"
			"Ils sont solides et robustes, mais se deplacent tres lentement.";
	tmpStock.clear();

	// wave 5
	tmpStock.push_back(new Gobelin(gameMap.getDoors()[0], gameMap));
	for(i=0; i<8; i++)
		tmpStock.push_back(new Enemy(gameMap.getDoors()[0], gameMap));
	for(i=0; i<5; i++)
	{
		tmpStock.push_back(new Gobelin(gameMap.getDoors()[0], gameMap));
		tmpStock.back()->waveWait = 1/4.f;
	}
	waves.push_back(Wave(&gameMap, 1.3f));
	waves.back().initStock(tmpStock);
	waves.back().value = 250;
	waves.back().message = "Les ennemis pourraient arriver du bas...";
	tmpStock.clear();

	// wave 6
	for(i=0; i<3; i++)
	{
		tmpStock.push_back(new Enemy(gameMap.getDoors()[0], gameMap));		
		tmpStock.push_back(new Drake(gameMap.getDoors()[0], gameMap));
		tmpStock.back()->waveWait = 1/4.f;
		tmpStock.push_back(new Gobelin(gameMap.getDoors()[0], gameMap));
	}
	waves.push_back(Wave(&gameMap, 1/1.f));
	waves.back().initStock(tmpStock);
	waves.back().message = "Protegez le sud le plus vite possible !";
	waves.back().value = 200;
	tmpStock.clear();

	// wave 7
	for(i=0; i<8; i++)
		tmpStock.push_back(new Enemy(gameMap.getDoors()[1], gameMap));
	waves.push_back(Wave(&gameMap, 1/1.f));
	waves.back().initStock(tmpStock);
	waves.back().value = 180;
	tmpStock.clear();

	// wave 8
	for(i=0; i<5; i++)
	{
		tmpStock.push_back(new Drake(gameMap.getDoors()[i%2], gameMap));
	}
	for(i=0; i<5; i++)
	{
		tmpStock.push_back(new Enemy(gameMap.getDoors()[i%2], gameMap));
	}
	for(i=0; i<5; i++)
	{
		tmpStock.push_back(new Gobelin(gameMap.getDoors()[i%2], gameMap));
		tmpStock.back()->waveWait = 1/6.f;
	}
	waves.push_back(Wave(&gameMap, 1/2.f));
	waves.back().initStock(tmpStock);
	waves.back().value = 200;
	waves.back().message = "C'est la derniere vague !";
	tmpStock.clear();


	return waves;
}
