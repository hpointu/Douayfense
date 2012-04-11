#ifndef DRAKE_HPP
#define DRAKE_HPP

#include "Enemy.hpp"

class Drake : public Enemy
{
public:
	Drake(Map::Cell pos, Map map);
	virtual sf::Image* getImage();
	virtual Enemy* createClone();
	virtual float getInitialPv();
	virtual void playDyingSound();
	virtual float getRealSpeed();
	virtual void applyPoison();
	virtual int getValue();

	virtual bool isFreezable(){ return false; }
};

#endif // DRAKE_HPP
