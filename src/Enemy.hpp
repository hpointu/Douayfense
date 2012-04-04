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

	void moveToNext();

private:
	sf::Sprite sprite;
	float speed;
	Map myMap;
};

#endif // ENEMY_HPP
