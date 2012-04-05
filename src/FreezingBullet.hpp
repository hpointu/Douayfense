#ifndef FREEZINGBULLET_HPP
#define FREEZINGBULLET_HPP

#include "Bullet.hpp"
#include <SFML/Graphics.hpp>


class FreezingBullet : public Bullet
{
public:
	FreezingBullet(float x, float y, Enemy *e, int damage);
	virtual void applyDamage();
	virtual sf::Shape getDrawable();

};

#endif // FREEZINGBULLET_HPP
