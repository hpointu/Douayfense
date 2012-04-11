#ifndef WOSEBULLET_HPP
#define WOSEBULLET_HPP

#include "Bullet.hpp"
#include <SFML/Graphics.hpp>


class WoseBullet : public Bullet
{
public:
	WoseBullet(float x, float y, Enemy *e, int damage);
	virtual void applyDamage();
	virtual sf::Shape getDrawable();

};

#endif // WOSEBULLET_HPP
