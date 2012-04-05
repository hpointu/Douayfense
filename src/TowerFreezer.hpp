#ifndef TOWERFREEZER_HPP
#define TOWERFREEZER_HPP

#include "Tower.hpp"
#include <string>
#include <SFML/Graphics.hpp>
#include "Enemy.hpp"

class TowerFreezer : public Tower
{
public:
	TowerFreezer();

	virtual Tower* getCopy();
	virtual void upgrade();
	virtual std::string upgradeDescription();
	virtual std::string getName();
	virtual sf::Image* getImage();
	virtual bool isValid(Enemy *e);
	virtual Bullet* createBullet(float x, float y, Enemy *e, int damage);

};

#endif // TOWERFREEZER_HPP
