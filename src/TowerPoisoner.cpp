#include "TowerPoisoner.hpp"
#include "Application.hpp"
#include "PoisoningBullet.hpp"
#include "SoundManager.hpp"

TowerPoisoner::TowerPoisoner() :
	Tower()
{
	price = 260;
	speed = 3;
	damage = 15;
	range = 90;
}

void TowerPoisoner::upgrade()
{
	if(!upgraded)
	{
		range *= 2;
		upgraded = true;
		sprite = sf::Sprite(*this->getImage());
	}
}

Tower* TowerPoisoner::getCopy()
{
	return new TowerPoisoner(*this);
}

sf::Image* TowerPoisoner::getImage()
{
	if(!upgraded)
		return &Application::getInstance()->poisonerImage;
	else
		return &Application::getInstance()->poisonerImageUp;
}

std::string TowerPoisoner::upgradeDescription()
{
	return "Double la distance d'attaque";
}


std::string TowerPoisoner::getDescription()
{
	return "Blesse et empoisonne les ennemis";
}

std::string TowerPoisoner::getName()
{
	if(!upgraded)
		return "Fleches empoisonnees";
	else
		return "Fleches empoisonnees longue portee";
}

bool TowerPoisoner::isValid(Enemy *e)
{
	return !e->poisoned;
}

Bullet* TowerPoisoner::createBullet(float x, float y, Enemy *e, int damage)
{
	SoundManager::getInstance()->playSound(Application::getInstance()->fireBuff, 70, 1.1f);
	return new PoisoningBullet(x,y,e,damage);
}
