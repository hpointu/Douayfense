#include "Drake.hpp"
#include "Application.hpp"
#include "SoundManager.hpp"

Drake::Drake(Map::Cell pos, Map map) :
	Enemy(pos, map)
{
	speed = 1.2f;
}

sf::Image* Drake::getImage()
{
	return &Application::getInstance()->drakeImage;
}

Enemy* Drake::createClone()
{
	return new Drake(*this);
}

float Drake::getInitialPv()
{
	return 350;
}

void Drake::playDyingSound()
{
	SoundManager::getInstance()->playSound(Application::getInstance()->dyingBuff, 80, 0.5f);
}

float Drake::getRealSpeed()
{
	return speed;
}

void Drake::applyPoison()
{
	Enemy::applyPoison();
}

int Drake::getValue()
{
	return 90;
}
