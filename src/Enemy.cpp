#include "Enemy.hpp"
#include "Application.hpp"
#include "Const.hpp"
#include <cmath>
#include <iostream>

Enemy::Enemy(Map::Cell pos, Map map) :
	myMap(map)
{
	x = pos.posJ*CELL_SIZE;
	y = pos.posI*CELL_SIZE;
	sprite = sf::Sprite(Application::getInstance()->enemyImage);
	speed = 2.2f;
	pv = 150;
	basePv = pv;
	frozen = false;
}

void Enemy::render(sf::RenderTarget *target)
{
	if(!isDead())
	{
		sprite.SetPosition(x-(Application::getInstance()->enemyImage.GetWidth()/2.f),
								 y-(CELL_SIZE/2.f)-(Application::getInstance()->enemyImage.GetHeight()/2.f));

		if(frozen)
			sprite.SetColor(sf::Color(100,100,255));
		target->Draw(sprite);

		if(pv < basePv)
		{
			// draw pv
			sf::Shape border = sf::Shape::Rectangle(x - (Application::getInstance()->enemyImage.GetWidth()/2.f) - 8,
																 y - (Application::getInstance()->enemyImage.GetHeight()) - 6,
																 x - (Application::getInstance()->enemyImage.GetWidth()/2.f) + 8,
																 y - (Application::getInstance()->enemyImage.GetHeight()) - 1,
																 sf::Color(0,0,0,0),
																 1.f,
																 sf::Color::White
																 );

			float pw = ((float)pv/basePv) * 16;
			sf::Shape fill = sf::Shape::Rectangle(x - (Application::getInstance()->enemyImage.GetWidth()/2.f) - 8,
																 y - (Application::getInstance()->enemyImage.GetHeight()) - 6,
																 x - (Application::getInstance()->enemyImage.GetWidth()/2.f) - 8 + pw,
																 y - (Application::getInstance()->enemyImage.GetHeight()) - 1,
																 sf::Color::White
																 );

			target->Draw(fill);
			target->Draw(border);
		}
	}
}

void Enemy::moveToNext()
{
	Map::Cell current = myMap.getCell(x,y);
	Map::Cell dest = myMap.nextPathCellFrom(current);

	float toX = dest.posJ*CELL_SIZE + CELL_SIZE/2.f;
	float toY = dest.posI*CELL_SIZE + CELL_SIZE/2.f;

	float dX = toX-x;
	float dY = toY-y;

	float realSpeed = frozen ? speed/2.f : speed;

	float err = realSpeed/2.f;

	if(::fabs(dX) > err)
		x += (dX>0) ? realSpeed : -realSpeed;

	if(::fabs(dY) > err)
		y += (dY>0) ? realSpeed : -realSpeed;

	myMap.setVisited(current.posI, current.posJ, true);
}

void Enemy::hurt(int damage)
{
	if(!isDead())
	{
		pv -= damage;
		if(pv < 0)
			pv = 0;

		if(isDead())
			Application::getInstance()->addMoney(basePv/3);
	}
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
