#ifndef BULLET_HPP
#define BULLET_HPP

#include <SFML/Graphics.hpp>
#include "Enemy.hpp"

class Bullet
{
public:
	Bullet(float x, float y, Enemy *e, int damage);

	void render(sf::RenderTarget *target);
	void tick();

	virtual void applyDamage();
	virtual sf::Shape getDrawable();

	bool dead;

protected:
	Enemy *enemy;
	float x, y;
	int damage;
};

#endif // BULLET_HPP
