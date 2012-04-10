#ifndef GOBELIN_HPP
#define GOBELIN_HPP

#include "Enemy.hpp"

class Gobelin : public Enemy
{
public:
	Gobelin(Map::Cell pos, Map map);
	virtual sf::Image* getImage();
	virtual Enemy* createClone();
	virtual float getInitialPv();
	virtual void playDyingSound();

};

#endif // GOBELIN_HPP
