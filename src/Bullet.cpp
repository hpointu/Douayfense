#include "Bullet.hpp"
#include <cmath>

Bullet::Bullet(float x, float y, Enemy *e, int damage) :
	enemy(e),
	x(x),
	y(y),
	damage(damage)
{
	dead = false;
}


sf::Shape Bullet::getDrawable()
{
	return sf::Shape::Circle(x, y, 3.f, sf::Color::Red);
}

void Bullet::tick()
{
	if(!dead)
	{
		float speed = 10.f;

		float toX = enemy->x;
		float toY = enemy->y;

		float dX = toX-x;
		float dY = toY-y;

		float err = 4.f;

		float dist = ::sqrt((dX*dX) + (dY*dY));
		float cos = dX/dist;
		float sin = dY/dist;

		if(::fabs(dX) > err)
			x += speed*cos;

		if(::fabs(dY) > err)
			y += speed*sin;

		if(::fabs(dX) <= err && ::fabs(dY) <= err)
		{
			this->applyDamage();
		}
	}

}

void Bullet::render(sf::RenderTarget *target)
{
	if(!dead && !enemy->isDead())
	{
//		shape.SetPosition(x, y);
		target->Draw(getDrawable());
	}
}

void Bullet::applyDamage()
{
	enemy->hurt(damage);
	dead = true;
}
