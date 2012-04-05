#include "Tower.hpp"
#include "Application.hpp"
#include "Const.hpp"

#include <cmath>
#include <iostream>

Tower::Tower() :
	selected(false),
	range(80),
	damage(25),
	speed(3),
	price(200)
{
	sprite = sf::Sprite(*this->getImage());
	wrong = false;
	upgraded = false;
	lastShot = 0.f;
}

sf::Image* Tower::getImage()
{
	if(!upgraded)
		return &Application::getInstance()->towerImage;
	else
		return &Application::getInstance()->towerImageUp;
}

Tower* Tower::createCopy()
{
	Tower *t = new Tower(*this);
	t->wrong = false;
	return t;
}

void Tower::upgrade()
{
	if(!upgraded)
	{
		speed *= 2;
		upgraded = true;
		sprite = sf::Sprite(*this->getImage());
	}
}

std::string Tower::upgradeDescription()
{
	return "Double la vitesse d'attaque";
}

std::string Tower::getName()
{
	if(upgraded)
		return "Tourelle militaire";
	else
		return "Tourelle de base";
}

void Tower::render(sf::RenderTarget *target, bool ghost)
{
	sf::Vector2f center(j*CELL_SIZE + (CELL_SIZE/2.f), i*CELL_SIZE + (CELL_SIZE/2.f));
	sprite.SetPosition(j*CELL_SIZE,
							 i*CELL_SIZE - (Application::getInstance()->towerImage.GetHeight()/2.5f)
							 );

	if(ghost)
	{
		sprite.SetColor(sf::Color(255,255,255,180));
	}
	else
	{
		sprite.SetColor(sf::Color(255,255,255));
	}

	if(ghost || selected)
	{
		sf::Color c1, c2;
		if(!wrong)
		{
			c1 = sf::Color(0,200,0,40);
			if(!upgraded)
				c2 = sf::Color(0,200,0,100);
			else
				c2 = sf::Color(200,200,0,100);
		}
		else
		{
			c1 = sf::Color(200,0,0,40);
			c2 = sf::Color(200,0,0,100);
		}
		sf::Shape rangeCircle = sf::Shape::Circle(center, range, c1, 2.f, c2);
		target->Draw(rangeCircle);
	}
	target->Draw(sprite);

	std::vector<Bullet*>::iterator bit;
	for(bit=bullets.begin(); bit!=bullets.end(); bit++)
	{
		(*bit)->render(target);
	}
}

void Tower::shoot(std::vector<Enemy*> enemies)
{
	if(clock.GetElapsedTime() - lastShot >= 2.f/speed)
	{
		sf::Vector2f center(j*CELL_SIZE + (CELL_SIZE/2.f), i*CELL_SIZE + (CELL_SIZE/2.f));
		std::vector<Enemy*>::iterator it;
		for(it=enemies.begin(); it!=enemies.end(); it++)
		{
			Enemy *e = *it;
			float dx = ::fabs(center.x - e->x);
			float dy = ::fabs(center.y - e->y);
			float dist = ::sqrt((dx*dx) + (dy*dy));
			if(dist <= range)
			{
				lastShot = clock.GetElapsedTime();
				if(!e->isDead())
				{
					bullets.push_back(new Bullet(center.x, center.y, e, damage));
					break;
				}
			}
		}
	}
	std::vector<Bullet*>::iterator bit;
	for(bit=bullets.begin(); bit!=bullets.end(); bit++)
	{
		(*bit)->tick();
	}
}
