#include "Tower.hpp"
#include "Application.hpp"
#include "SoundManager.hpp"
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
	active = true;
	lastShot = 0.f;

	clock = &Application::getInstance()->gameClock;
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
	Tower *t = this->getCopy();
	t->wrong = false;
	return t;
}

Tower* Tower::getCopy()
{
	return new Tower(*this);
}

void Tower::upgrade()
{
	if(!upgraded)
	{
		speed *= 1.4;
		upgraded = true;
		sprite = sf::Sprite(*this->getImage());
	}
}

std::string Tower::upgradeDescription()
{
	return "Augmente la vitesse d'attaque";
}

std::string Tower::getDescription()
{
	return "Blesse les ennemis";
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
	if(active)
	{
		sprite = sf::Sprite(*this->getImage());
		sf::Vector2f center(j*CELL_SIZE + (CELL_SIZE/2.f), i*CELL_SIZE + (CELL_SIZE/2.f));
		sprite.SetPosition(j*CELL_SIZE,
								 i*CELL_SIZE - (this->getImage()->GetHeight()/2.5f)
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
				c1 = sf::Color(0,0,200,40);
				if(!upgraded)
					c2 = sf::Color(0,0,200,100);
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
}

Bullet* Tower::createBullet(float x, float y, Enemy *e, int damage)
{
	SoundManager::getInstance()->playSound(Application::getInstance()->fireBuff, 70, 1.5f);
	return new Bullet(x,y,e,damage);
}

bool Tower::isValid(Enemy *e)
{
	return true;
}

void Tower::shoot(std::vector<Enemy*> enemies)
{
	if(active)
	{
		if(clock->GetElapsedTime() - lastShot >= 2.f/speed)
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
					lastShot = clock->GetElapsedTime();
					if(!e->isDead() && isValid(e))
					{
						bullets.push_back(this->createBullet(center.x, center.y, e, damage));
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
}
