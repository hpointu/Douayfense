#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "Map.hpp"
#include <SFML/Graphics.hpp>

class Enemy
{
public:
	Enemy(Map::Cell pos, Map map);
	~Enemy();

	void render(sf::RenderTarget *target);

	float x, y;
	float pv;
	bool frozen;
	bool poisoned;

	void tick();
	bool isDead();
	bool atHome();

	void hurt(float damage);
	void win();

private:
	void moveToNext();
	sf::Sprite sprite;
	Map myMap;


	float speed;

	float basePv;
};

#endif // ENEMY_HPP
