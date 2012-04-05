#include "Wave.hpp"

Wave::Wave(Map *map, float freq) :
	gameMap(map),
	freq(freq)
{

}

void Wave::initStock(const std::vector<Enemy> &list)
{
	stock.clear();
	stock = list;

	value = 10*stock.size();
}

bool Wave::hasStock()
{
	return !stock.empty();
}

Enemy* Wave::getNextEnemy()
{
	Enemy *e = NULL;

	if(hasStock() && clock.GetElapsedTime()-lastToken >= freq)
	{
		e = new Enemy(stock.front());
		stock.erase(stock.begin());
		lastToken = clock.GetElapsedTime();
	}

	return e;
}
