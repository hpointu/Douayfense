#ifndef POISONINGBULLET_HPP
#define POISONINGBULLET_HPP

#include "Bullet.hpp"
#include <SFML/Graphics.hpp>

class PoisoningBullet : public Bullet
{
public:
	PoisoningBullet(float x, float y, Enemy *e, int damage);
	virtual void applyDamage();
	virtual sf::Shape getDrawable();
};

#endif // POISONINGBULLET_HPP
