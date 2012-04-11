#include "WoseBullet.hpp"
#include <iostream>

WoseBullet::WoseBullet(float x, float y, Enemy *e, int damage) :
	Bullet(x,y,e,damage)
{
}

void WoseBullet::applyDamage()
{
	enemy->rootMe(2.5f);
	dead = true;
}

sf::Shape WoseBullet::getDrawable()
{
	return sf::Shape::Circle(x, y, 2.f, sf::Color::Black);
}
