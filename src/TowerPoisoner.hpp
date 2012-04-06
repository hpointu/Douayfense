#ifndef TOWERPOISONER_HPP
#define TOWERPOISONER_HPP

#include "Tower.hpp"
#include <string>
#include <SFML/Graphics.hpp>
#include "Enemy.hpp"

class TowerPoisoner : public Tower
{
public:
	TowerPoisoner();

	virtual Tower* getCopy();
	virtual void upgrade();
	virtual std::string upgradeDescription();
	virtual std::string getName();
	virtual std::string getDescription();
	virtual sf::Image* getImage();
	virtual bool isValid(Enemy *e);
	virtual Bullet* createBullet(float x, float y, Enemy *e, int damage);
};

#endif // TOWERPOISONER_HPP
