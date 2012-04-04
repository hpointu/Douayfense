#include "Enemy.hpp"
#include "Application.hpp"
#include "Const.hpp"
#include <cmath>

Enemy::Enemy(Map::Cell pos, Map map) :
	myMap(map)
{
	x = pos.posJ*CELL_SIZE;
	y = pos.posI*CELL_SIZE;
	sprite = sf::Sprite(Application::getInstance()->enemyImage);
	speed = 3.2f;
	pv = 100;
}

void Enemy::render(sf::RenderTarget *target)
{
	if(!isDead())
	{
		sprite.SetPosition(x-(Application::getInstance()->enemyImage.GetWidth()/1.3f),
								 y-(Application::getInstance()->enemyImage.GetHeight() + 8));
		target->Draw(sprite);
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

	float err = speed/2.f;

	if(::fabs(dX) > err)
		x += (dX>0) ? speed : -speed;

	if(::fabs(dY) > err)
		y += (dY>0) ? speed : -speed;

	myMap.setVisited(current.posI, current.posJ, true);
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
