#ifndef TOWERWOSE_HPP
#define TOWERWOSE_HPP

#include "Tower.hpp"
#include <string>
#include <SFML/Graphics.hpp>
#include "Enemy.hpp"

class TowerWose : public Tower
{
public:
	TowerWose();

	virtual Tower* getCopy();
	virtual void upgrade();
	virtual std::string upgradeDescription();
	virtual std::string getName();
	virtual std::string getDescription();
	virtual sf::Image* getImage();
	virtual bool isValid(Enemy *e);
	virtual Bullet* createBullet(float x, float y, Enemy *e, int damage);
};

#endif // TOWERWOSE_HPP
