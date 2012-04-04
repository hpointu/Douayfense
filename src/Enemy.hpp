#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "Map.hpp"
#include <SFML/Graphics.hpp>

class Enemy
{
public:
	Enemy(Map::Cell pos, Map map);

	void render(sf::RenderTarget *target);

	float x, y;
	int pv;

	void moveToNext();
	bool isDead();
	bool atHome();

private:
	sf::Sprite sprite;
	Map myMap;

	float speed;
};

#endif // ENEMY_HPP
