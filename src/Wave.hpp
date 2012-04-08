#ifndef WAVE_HPP
#define WAVE_HPP

#include "Enemy.hpp"
#include "Map.hpp"
#include <vector>
#include <SFML/Graphics.hpp>
#include <string>
#include "PausableClock.hpp"

class Wave
{
public:
	Wave(Map *map, float freq);
	virtual void initStock(const std::vector<Enemy> &list);

	Enemy* getNextEnemy();

	bool hasStock();

	int value;

	std::string message;

private:
	std::vector<Enemy> stock;
	PausableClock *clock;
	Map *gameMap;
	float freq;
	float lastToken;
};

#endif // WAVE_HPP
