#include "FreezingBullet.hpp"
#include <iostream>

FreezingBullet::FreezingBullet(float x, float y, Enemy *e, int damage) :
	Bullet(x,y,e,damage)
{
}

void FreezingBullet::applyDamage()
{
	enemy->frozen = true;
	dead = true;
}

sf::Shape FreezingBullet::getDrawable()
{
	return sf::Shape::Circle(x, y, 4.f, sf::Color::Cyan);
}
