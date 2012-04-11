#include "TowerFreezer.hpp"
#include "Application.hpp"
#include "FreezingBullet.hpp"
#include "SoundManager.hpp"

TowerFreezer::TowerFreezer() :
	Tower()
{
	price = 150;
	speed = 3;
	damage = 0;
	range = 90;
}

void TowerFreezer::upgrade()
{
	if(!upgraded)
	{
		range *= 1.5;
		speed *= 1.5;
		upgraded = true;
		sprite = sf::Sprite(*this->getImage());
	}
}

Tower* TowerFreezer::getCopy()
{
	return new TowerFreezer(*this);
}

sf::Image* TowerFreezer::getImage()
{
	if(!upgraded)
		return &Application::getInstance()->freezerImage;
	else
		return &Application::getInstance()->freezerImageUp;
}

std::string TowerFreezer::upgradeDescription()
{
	return "Augmente la distance d'attaque et la vitesse d'attaque";
}

std::string TowerFreezer::getDescription()
{
	return "Ralentit les ennemis";
}


std::string TowerFreezer::getName()
{
	if(upgraded)
		return "Lanceur de givre longue portee";
	else
		return "Lanceur de givre";
}

bool TowerFreezer::isValid(Enemy *e)
{
	return e->isFreezable() && !e->frozen;
}

Bullet* TowerFreezer::createBullet(float x, float y, Enemy *e, int damage)
{
	SoundManager::getInstance()->playSound(Application::getInstance()->fireBuff, 70, 2.2f);
	return new FreezingBullet(x,y,e,damage);
}
