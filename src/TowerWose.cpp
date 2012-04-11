#include "TowerWose.hpp"
#include "Application.hpp"
#include "WoseBullet.hpp"
#include "SoundManager.hpp"

TowerWose::TowerWose() :
	Tower()
{
	price = 275;
	speed = 2;
	damage = 0;
	range = 50;
}

void TowerWose::upgrade()
{
	if(!upgraded)
	{
		speed *= 2;
		upgraded = true;
		sprite = sf::Sprite(*this->getImage());
	}
}

Tower* TowerWose::getCopy()
{
	return new TowerWose(*this);
}

sf::Image* TowerWose::getImage()
{
	if(!upgraded)
		return &Application::getInstance()->woseImage;
	else
		return &Application::getInstance()->woseImageUp;
}

std::string TowerWose::upgradeDescription()
{
	return "Augmente la vitesse d'attaque";
}


std::string TowerWose::getDescription()
{
	return "Immobilise temporairement les ennemis";
}

std::string TowerWose::getName()
{
	if(!upgraded)
		return "Wose";
	else
		return "Wose venerable";
}

bool TowerWose::isValid(Enemy *e)
{
	return !e->isRooted();
}

Bullet* TowerWose::createBullet(float x, float y, Enemy *e, int damage)
{
	SoundManager::getInstance()->playSound(Application::getInstance()->fireBuff, 70, 0.8f);
	return new WoseBullet(x,y,e,damage);
}
