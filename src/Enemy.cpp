#include "Enemy.hpp"
#include "SoundManager.hpp"
#include "Application.hpp"
#include "Const.hpp"
#include <cmath>
#include <iostream>

Enemy::Enemy(Map::Cell pos, Map map) :
	myMap(map)
{
	x = pos.posJ*CELL_SIZE;
	y = pos.posI*CELL_SIZE;
	sprite = sf::Sprite(*getImage());
	speed = 2.2f;
	frozen = false;
	poisoned = false;
	waveWait = -1;
}

Enemy::~Enemy()
{
}

void Enemy::init()
{
	pv = getInitialPv();
}

float Enemy::getInitialPv()
{
	return 150;
}

sf::Image* Enemy::getImage()
{
	return &Application::getInstance()->skelImage;
}

Enemy* Enemy::createClone()
{
	return new Enemy(*this);
}

void Enemy::render(sf::RenderTarget *target)
{
	if(!isDead())
	{
		sprite = sf::Sprite(*getImage());
		sprite.SetPosition(x-(getImage()->GetWidth()/2.f),
								 y-(CELL_SIZE/2.f)-(getImage()->GetHeight()/2.f));

		if(frozen)
			sprite.SetColor(sf::Color(100,100,255));
		target->Draw(sprite);

		if(pv < getInitialPv())
		{
			// draw pv
			sf::Color borderColor = poisoned ? sf::Color(120,200,80) : sf::Color::White;
			sf::Shape border = sf::Shape::Rectangle(x - (getImage()->GetWidth()/2.f) - 8,
																 y - (getImage()->GetHeight()) - 6,
																 x - (getImage()->GetWidth()/2.f) + 8,
																 y - (getImage()->GetHeight()) - 1,
																 sf::Color(0,0,0,0),
																 1.f,
																 borderColor
																 );

			float pw = ((float)pv/getInitialPv()) * 16;
			sf::Shape fill = sf::Shape::Rectangle(x - (getImage()->GetWidth()/2.f) - 8,
																 y - (getImage()->GetHeight()) - 6,
																 x - (getImage()->GetWidth()/2.f) - 8 + pw,
																 y - (getImage()->GetHeight()) - 1,
																 sf::Color::White
																 );

			target->Draw(fill);
			target->Draw(border);
		}
	}
}

float Enemy::getRealSpeed()
{
	return frozen ? speed/2.f : speed;
}

void Enemy::tick()
{
	moveToNext();

	if(poisoned)
	{
		applyPoison();
	}
}

void Enemy::freezeMe()
{
	frozen = true;
}

void Enemy::applyPoison()
{
	hurt(0.15);
}

void Enemy::moveToNext()
{
	Map::Cell current = myMap.getCell(x,y);
	Map::Cell dest = myMap.nextPathCellFrom(current);

	float toX = dest.posJ*CELL_SIZE + CELL_SIZE/2.f;
	float toY = dest.posI*CELL_SIZE + CELL_SIZE/2.f;

	float dX = toX-x;
	float dY = toY-y;

	float realSpeed = getRealSpeed();

	float err = realSpeed/2.f;

	if(::fabs(dX) > err)
		x += (dX>0) ? realSpeed : -realSpeed;

	if(::fabs(dY) > err)
		y += (dY>0) ? realSpeed : -realSpeed;

	myMap.setVisited(current.posI, current.posJ, true);
}

void Enemy::playDyingSound()
{
	SoundManager::getInstance()->playSound(Application::getInstance()->dyingBuff, 70, 1.f);

}

void Enemy::win()
{
	pv = 0;
	SoundManager::getInstance()->playSound(Application::getInstance()->dingBuff, 80, 1.5f);
}

void Enemy::hurt(float damage)
{
//	std::cout << pv << std::endl;
	if(!isDead())
	{
		pv -= damage;
		if(pv < 0)
			pv = 0;

		if(isDead())
		{
			playDyingSound();
			Application::getInstance()->addMoney(getValue());
		}
	}
}

int Enemy::getValue()
{
	return getInitialPv()/4.f;
}

bool Enemy::isDead()
{
	return pv <= 0;
}

bool Enemy::atHome()
{
	Map::Cell current = myMap.getCell(x,y);
	return current.type == Map::HOME;
}
