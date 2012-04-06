#include "PoisoningBullet.hpp"

PoisoningBullet::PoisoningBullet(float x, float y, Enemy *e, int damage) :
	Bullet(x,y,e,damage)
{
}

void PoisoningBullet::applyDamage()
{
	enemy->hurt(damage);
	enemy->poisoned = true;
	dead = true;
}

sf::Shape PoisoningBullet::getDrawable()
{
	return sf::Shape::Circle(x, y, 3.f, sf::Color(120,200,80));
}
